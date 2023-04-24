#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <jac/link/mux.h>
#include <jac/link/stream.h>
#include <jac/link/encoders/cobs.h>

#include <numeric>

#include "util.h"


using namespace jac;


class BufferRx {
    class Handle : public ChannelReceiver {
        BufferRx* _rx;
    public:
        Handle(BufferRx* rx) : _rx(rx) {}
        Handle& operator=(const Handle&) = delete;
        Handle(const Handle&) = delete;

        Handle& operator=(Handle&& other) {
            _rx = other._rx;
            other._rx = nullptr;
            return *this;
        }
        Handle(Handle&& other) {
            *this = std::move(other);
        }

        void processPacket(uint8_t channel, std::span<const uint8_t> data) override {
            _rx->packets.push_back({channel, std::vector<uint8_t>(data.begin(), data.end())});
        }
    };
public:
    std::deque<std::pair<uint8_t, std::vector<uint8_t>>> packets;

    Handle getHandle() {
        return Handle(this);
    }
};


TEST_CASE("Send-receive packet", "[mux]") {
    auto inStream1 = std::make_unique<BufferStream>();
    auto outStream1 = std::make_unique<BufferStream>();
    // auto& in1 = *inStream1;
    auto& out1 = *outStream1;
    auto mux1 = Mux<CobsEncoder>(std::make_unique<Duplexify>(std::move(inStream1), std::move(outStream1)));
    mux1.setErrorHandler([](Mux<CobsEncoder>::Error error, std::any ctx) {
        CAPTURE(error);
        CAPTURE(ctx);
        FAIL("Error handler called");
    });

    auto inStream2 = std::make_unique<BufferStream>();
    auto outStream2 = std::make_unique<BufferStream>();
    auto& in2 = *inStream2;
    // auto& out2 = *outStream2;
    auto mux2 = Mux<CobsEncoder>(std::make_unique<Duplexify>(std::move(inStream2), std::move(outStream2)));
    mux2.setErrorHandler([](Mux<CobsEncoder>::Error error, std::any ctx) {
        CAPTURE(error);
        CAPTURE(ctx);
        FAIL("Error handler called");
    });

    auto rx = BufferRx();
    mux2.bindRx(std::make_unique<decltype(rx.getHandle())>(rx.getHandle()));

    const auto capacity = mux1.maxPacketSize();
    using sgn = typename std::tuple<std::string, uint8_t, std::vector<uint8_t>>;
    auto [comment, channel, original] = GENERATE_COPY(
        sgn{ "Empty packet", 0, {} },
        sgn{ "Single byte", 0, { 0x01 } },
        sgn{ "Two bytes", 0, { 0x01, 0x02 } },
        sgn{ "Three bytes", 0, { 0x01, 0x02, 0x03 } },
        sgn{ "Full packet", 0, rangeVector<uint8_t>(0, capacity) },
        sgn{ "Full packet, ch1", 1, rangeVector<uint8_t>(0, capacity) },
        sgn{ "Full packet, ch255", 255, rangeVector<uint8_t>(0, capacity) }
    );
    DYNAMIC_SECTION(comment) {
        auto packet = mux1.buildPacket(channel);
        for (size_t i = 0; i < original.size(); ++i) {
            if (i < capacity - 1) {
                REQUIRE_FALSE(packet->put(original[i]));
            } else {
                REQUIRE(packet->put(original[i]));
            }
        }

        REQUIRE(packet->send());

        int c = 0;
        while ((c = out1.get()) != EOF) {
            in2.put(c);
        }

        REQUIRE(rx.packets.size() == 1);
        auto& [ch, received] = rx.packets[0];

        REQUIRE(ch == channel);
        REQUIRE(received == original);
    }
}


TEST_CASE("Overflow packet", "[mux]") {
    auto inStream1 = std::make_unique<BufferStream>();
    auto outStream1 = std::make_unique<BufferStream>();
    // auto& in1 = *inStream1;
    auto& out1 = *outStream1;
    auto mux1 = Mux<CobsEncoder>(std::make_unique<Duplexify>(std::move(inStream1), std::move(outStream1)));
    mux1.setErrorHandler([](Mux<CobsEncoder>::Error error, std::any ctx) {
        CAPTURE(error);
        CAPTURE(ctx);
        FAIL("Error handler called");
    });

    auto inStream2 = std::make_unique<BufferStream>();
    auto outStream2 = std::make_unique<BufferStream>();
    auto& in2 = *inStream2;
    // auto& out2 = *outStream2;
    auto mux2 = Mux<CobsEncoder>(std::make_unique<Duplexify>(std::move(inStream2), std::move(outStream2)));
    mux2.setErrorHandler([](Mux<CobsEncoder>::Error error, std::any ctx) {
        CAPTURE(error);
        CAPTURE(ctx);
        FAIL("Error handler called");
    });

    auto rx = BufferRx();
    mux2.bindRx(std::make_unique<decltype(rx.getHandle())>(rx.getHandle()));

    const auto capacity = mux1.maxPacketSize();
    using sgn = typename std::tuple<std::string, uint8_t, std::vector<uint8_t>>;
    auto [comment, channel, original] = sgn{ "Overflow packet, ch255", 255, rangeVector<uint8_t>(0, capacity + 10) };


    auto packet = mux1.buildPacket(channel);
    for (size_t i = 0; i < original.size(); ++i) {
        if (i < capacity - 1) {
            REQUIRE_FALSE(packet->put(original[i]));
        } else {
            REQUIRE(packet->put(original[i]));
        }
    }

    REQUIRE(packet->send());

    int c = 0;
    while ((c = out1.get()) != EOF) {
        in2.put(c);
    }

    REQUIRE(rx.packets.size() == 1);
    auto& [ch, received] = rx.packets[0];

    REQUIRE(ch == channel);

    CAPTURE(original);
    CAPTURE(received);
    REQUIRE(std::equal(original.begin(), original.begin() + capacity, received.begin(), received.end()));
}


TEST_CASE("Packets in succession", "[mux]") {
    auto inStream1 = std::make_unique<BufferStream>();
    auto outStream1 = std::make_unique<BufferStream>();
    // auto& in1 = *inStream1;
    auto& out1 = *outStream1;
    auto mux1 = Mux<CobsEncoder>(std::make_unique<Duplexify>(std::move(inStream1), std::move(outStream1)));
    mux1.setErrorHandler([](Mux<CobsEncoder>::Error error, std::any ctx) {
        CAPTURE(error);
        CAPTURE(ctx);
        FAIL("Error handler called");
    });

    auto inStream2 = std::make_unique<BufferStream>();
    auto outStream2 = std::make_unique<BufferStream>();
    auto& in2 = *inStream2;
    // auto& out2 = *outStream2;
    auto mux2 = Mux<CobsEncoder>(std::make_unique<Duplexify>(std::move(inStream2), std::move(outStream2)));
    mux2.setErrorHandler([](Mux<CobsEncoder>::Error error, std::any ctx) {
        CAPTURE(error);
        CAPTURE(ctx);
        FAIL("Error handler called");
    });

    auto rx = BufferRx();
    mux2.bindRx(std::make_unique<decltype(rx.getHandle())>(rx.getHandle()));

    const auto capacity = mux1.maxPacketSize();
    using sgn = typename std::tuple<std::string, uint8_t, std::vector<uint8_t>>;
    std::vector<sgn> packets = {
        sgn{ "Empty packet", 0, {} },
        sgn{ "Single byte", 0, { 0x01 } },
        sgn{ "Two bytes", 0, { 0x01, 0x02 } },
        sgn{ "Three bytes", 0, { 0x01, 0x02, 0x03 } },
        sgn{ "Full packet", 0, rangeVector<uint8_t>(0, capacity) },
        sgn{ "Full packet, ch1", 1, rangeVector<uint8_t>(0, capacity) },
        sgn{ "Full packet, ch255", 255, rangeVector<uint8_t>(0, capacity) }
    };
    size_t count = 0;
    for (auto& [comment, channel, original] : packets) {
        CAPTURE(count);
        auto packet = mux1.buildPacket(channel);
        for (size_t i = 0; i < original.size(); ++i) {
            if (i < capacity - 1) {
                REQUIRE_FALSE(packet->put(original[i]));
            } else {
                REQUIRE(packet->put(original[i]));
            }
        }

        REQUIRE(packet->send());

        int c = 0;
        while ((c = out1.get()) != EOF) {
            in2.put(c);
        }

        REQUIRE(rx.packets.size() == count + 1);
        auto& [ch, received] = rx.packets.back();

        REQUIRE(ch == channel);
        REQUIRE(received == original);
        ++count;
    }
}
