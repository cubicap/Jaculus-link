#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <jac/link/router.h>
#include <cstddef>
#include <unordered_map>

#include "util.h"


using namespace jac;


TEST_CASE("SubscribeTx", "[router]") {
    using sgn = typename std::tuple<std::string, std::vector<std::tuple<int, size_t>>>;

    auto [comment, txsParams] = GENERATE(
        sgn{ "single", { { 0, 256 } } },
        sgn{ "same size", { { 1, 256 }, { 2, 256 } } },
        sgn{ "different size", { { 1, 256 }, { 2, 128 } } },
        sgn{ "many", { { 1, 256 }, { 2, 128 }, { 3, 64 }, { 4, 32 }, { 5, 16 } } }
    );

    DYNAMIC_SECTION(comment) {
        Router router;

        std::vector<std::unique_ptr<BufferTransmitter>> transmitters;
        std::vector<std::unique_ptr<Router::Handle>> handles;

        for (size_t i = 0; i < txsParams.size(); i++) {
            auto [id, maxPacketSize] = txsParams[i];

            transmitters.push_back(std::make_unique<BufferTransmitter>(maxPacketSize));
            handles.push_back(std::make_unique<Router::Handle>(router.subscribeTx(id, *transmitters.back())));
            REQUIRE(transmitters[i]->maxPacketSize() == maxPacketSize);
            REQUIRE_THROWS(router.subscribeTx(id, *transmitters.back()));
        }

        for (size_t i = 0; i < txsParams.size(); i++) {
            auto [id, maxPacketSize] = txsParams[i];

            REQUIRE(router.maxPacketSize(0, {id}) == maxPacketSize);
        }

        size_t minPacketSize = std::get<1>(*std::min_element(txsParams.begin(), txsParams.end(), [](auto& a, auto& b) {
            return std::get<1>(a) < std::get<1>(b);
        }));
        REQUIRE(router.maxPacketSize(0, {}) == minPacketSize);

        handles.clear();
        for (size_t i = 0; i < txsParams.size(); i++) {
            auto [id, _] = txsParams[i];

            REQUIRE(router.maxPacketSize(0, {id}) == 0);
        }
    }
}


TEST_CASE("Receive", "[router]") {
    Router router;

    const std::vector<size_t> packetSizes = { 256, 256, 128 };
    const std::vector<int> consumedChannels = { 0, 1, 2 };

    std::vector<std::unique_ptr<BufferTransmitter>> transmitters;
    std::vector<std::unique_ptr<Router::Handle>> handles;

    for (uint8_t i = 0; i < packetSizes.size(); i++) {
        transmitters.push_back(std::make_unique<BufferTransmitter>(packetSizes[i]));
        handles.push_back(std::make_unique<Router::Handle>(router.subscribeTx(i, *transmitters.back())));
    }

    std::unordered_map<int, std::unique_ptr<BufferConsumer>> consumers;
    for (auto channel : consumedChannels) {
        consumers[channel] = std::make_unique<BufferConsumer>();
        router.subscribeChannel(channel, *consumers[channel]);
    }

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>, int, int>;
    auto [comment, data, sender, channel] = GENERATE_COPY(
        sgn{ "Single byte", { 0x00 }, 0, 0 },
        sgn{ "Two bytes", { 0x00, 0x01 }, 0, 0 },
        sgn{ "Three bytes", { 0x00, 0x01, 0x02 }, 0, 0 },
        sgn{ "One to full packet", rangeVector<uint8_t>(0, packetSizes[0] - 1), 0, 0 },
        sgn{ "Full packet", rangeVector<uint8_t>(0, packetSizes[0]), 0, 0 },
        sgn{ "Full packet, small tx", rangeVector<uint8_t>(0, packetSizes[2]), 2, 0 }
    );

    DYNAMIC_SECTION(comment) {
        handles[sender]->processPacket(channel, std::span(data.begin(), data.end()));

        for (auto& [_channel, _consumer] : consumers) {
            if (_channel == channel) {
                REQUIRE(_consumer->_packets.size() == 1);
                auto& [_sender, _data] = _consumer->_packets[0];
                REQUIRE(_sender == sender);
                REQUIRE(_data == data);
            } else {
                REQUIRE(_consumer->_packets.size() == 0);
            }
        }
    }
}


TEST_CASE("Send", "[router]") {
    Router router;

    const std::vector<size_t> packetSizes = { 256, 256, 128 };

    std::vector<std::unique_ptr<BufferTransmitter>> transmitters;
    std::vector<std::unique_ptr<Router::Handle>> handles;

    for (uint8_t i = 0; i < packetSizes.size(); i++) {
        transmitters.push_back(std::make_unique<BufferTransmitter>(packetSizes[i]));
        handles.push_back(std::make_unique<Router::Handle>(router.subscribeTx(i, *transmitters.back())));
    }

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>, int, int>;
    auto [comment, data, recipient, channel] = GENERATE_COPY(
        sgn{ "Single byte", { 0x00 }, 0, 0 },
        sgn{ "Two bytes", { 0x00, 0x01 }, 0, 1 },
        sgn{ "Three bytes", { 0x00, 0x01, 0x02 }, 0, 2 },
        sgn{ "One to full packet", rangeVector<uint8_t>(0, packetSizes[0] - 1), 0, 0 },
        sgn{ "Full packet", rangeVector<uint8_t>(0, packetSizes[0]), 0, 1 },
        sgn{ "Full packet, small tx", rangeVector<uint8_t>(0, packetSizes[2]), 2, 2 }
    );

    DYNAMIC_SECTION(comment) {
        auto packet = router.buildPacket(channel, {recipient});
        REQUIRE(packet);
        REQUIRE(packet->put(std::span(data.begin(), data.end())) == data.size());
        REQUIRE(packet->send());

        for (size_t i = 0; i < transmitters.size(); i++) {
            if (static_cast<int>(i) == recipient) {
                REQUIRE(transmitters[i]->_packets.size() == 1);
                auto& [_channel, _data] = transmitters[i]->_packets[0];
                REQUIRE(_channel == channel);
                REQUIRE(_data == data);
            } else {
                REQUIRE(transmitters[i]->_packets.size() == 0);
            }
        }
    }
}


TEST_CASE("Broadcast - multiple transmitters", "[router]") {
    Router router;

    const std::vector<size_t> packetSizes = { 256, 256, 128 };
    size_t minPacketSize = *std::min_element(packetSizes.begin(), packetSizes.end());

    std::vector<std::unique_ptr<BufferTransmitter>> transmitters;
    std::vector<std::unique_ptr<Router::Handle>> handles;

    for (uint8_t i = 0; i < packetSizes.size(); i++) {
        transmitters.push_back(std::make_unique<BufferTransmitter>(packetSizes[i]));
        handles.push_back(std::make_unique<Router::Handle>(router.subscribeTx(i, *transmitters.back())));
    }

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>, int>;
    auto [comment, data, channel] = GENERATE_COPY(
        sgn{ "Single byte", { 0x00 }, 0 },
        sgn{ "Two bytes", { 0x00, 0x01 }, 1 },
        sgn{ "Three bytes", { 0x00, 0x01, 0x02 }, 2 },
        sgn{ "One to full packet", rangeVector<uint8_t>(0, minPacketSize - 1), 0 },
        sgn{ "Full packet", rangeVector<uint8_t>(0, minPacketSize), 1 }
    );

    DYNAMIC_SECTION(comment) {
        auto packet = router.buildPacket(channel, {});
        REQUIRE(packet);
        REQUIRE(packet->put(std::span(data.begin(), data.end())) == data.size());
        REQUIRE(packet->send());

        for (size_t i = 0; i < transmitters.size(); i++) {
            REQUIRE(transmitters[i]->_packets.size() == 1);
            auto& [_channel, _data] = transmitters[i]->_packets[0];
            REQUIRE(_channel == channel);
            REQUIRE(_data == data);
        }
    }
}


TEST_CASE("Broadcast - single transmitter", "[router]") {
    Router router;

    const size_t PACKET_SIZE = 256;

    BufferTransmitter transmitter(PACKET_SIZE);
    auto handle = router.subscribeTx(0, transmitter);

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>, int>;
    auto [comment, data, channel] = GENERATE_COPY(
        sgn{ "Single byte", { 0x00 }, 0 },
        sgn{ "Two bytes", { 0x00, 0x01 }, 1 },
        sgn{ "Three bytes", { 0x00, 0x01, 0x02 }, 2 },
        sgn{ "One to full packet", rangeVector<uint8_t>(0, PACKET_SIZE - 1), 0 },
        sgn{ "Full packet", rangeVector<uint8_t>(0, PACKET_SIZE), 1 }
    );

    DYNAMIC_SECTION(comment) {
        auto packet = router.buildPacket(channel, {});
        REQUIRE(packet);
        REQUIRE(packet->put(std::span(data.begin(), data.end())) == data.size());
        REQUIRE(packet->send());

        REQUIRE(transmitter._packets.size() == 1);
        auto& [_channel, _data] = transmitter._packets[0];
        REQUIRE(_channel == channel);
        REQUIRE(_data == data);
    }
}


TEST_CASE("Multicast", "[router]") {
    Router router;

    const std::vector<size_t> packetSizes = { 64, 256, 128 };
    size_t minPacketSize = *std::min_element(packetSizes.begin(), packetSizes.end());

    std::vector<std::unique_ptr<BufferTransmitter>> transmitters;
    std::vector<std::unique_ptr<Router::Handle>> handles;

    for (uint8_t i = 0; i < packetSizes.size(); i++) {
        transmitters.push_back(std::make_unique<BufferTransmitter>(packetSizes[i]));
        handles.push_back(std::make_unique<Router::Handle>(router.subscribeTx(i, *transmitters.back())));
    }

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>, int, std::vector<int>, size_t>;
    auto [comment, data, channel, recipients, maxSize] = GENERATE_COPY(
        sgn{ "Single", rangeVector<uint8_t>(0, minPacketSize), 1, { 1 }, 256 },
        sgn{ "Multiple", rangeVector<uint8_t>(0, minPacketSize), 2, { 0, 2 }, 64 },
        sgn{ "All", rangeVector<uint8_t>(0, minPacketSize), 3, { 0, 1, 2 }, 64 },
        sgn{ "Broadcast", rangeVector<uint8_t>(0, minPacketSize), 4, {}, 64 },
        sgn{ "Multiple - out of order", rangeVector<uint8_t>(0, minPacketSize), 5, { 1, 2 }, 128 }
    );

    DYNAMIC_SECTION(comment) {
        auto packet = router.buildPacket(channel, recipients);
        REQUIRE(packet);
        REQUIRE(packet->put(std::span(data.begin(), data.end())) == data.size());
        REQUIRE(packet->send());

        REQUIRE(router.maxPacketSize(channel, recipients) == maxSize);

        for (size_t i = 0; i < transmitters.size(); i++) {
            if (recipients.empty() || std::find(recipients.begin(), recipients.end(), i) != recipients.end()) {
                REQUIRE(transmitters[i]->_packets.size() == 1);
                auto& [_channel, _data] = transmitters[i]->_packets[0];
                REQUIRE(_channel == channel);
                REQUIRE(_data == data);
            } else {
                REQUIRE(transmitters[i]->_packets.size() == 0);
            }
        }
    }
}


TEST_CASE("Overflow broadcast packet", "[router]") {
    Router router;

    const std::vector<size_t> packetSizes = { 256, 256, 128 };

    std::vector<std::unique_ptr<BufferTransmitter>> transmitters;
    std::vector<std::unique_ptr<Router::Handle>> handles;

    for (uint8_t i = 0; i < packetSizes.size(); i++) {
        transmitters.push_back(std::make_unique<BufferTransmitter>(packetSizes[i]));
        handles.push_back(std::make_unique<Router::Handle>(router.subscribeTx(i, *transmitters.back())));
    }


    const auto capacity = router.maxPacketSize(0, {});
    using sgn = typename std::tuple<std::string, uint8_t, std::vector<uint8_t>>;
    auto [comment, channel, original] = sgn{ "Overflow packet", 0, rangeVector<uint8_t>(0, capacity + 10) };


    auto packet = router.buildPacket(channel, {});
    for (size_t i = 0; i < original.size(); ++i) {
        CAPTURE(i);
        if (i < capacity - 1) {
            REQUIRE_FALSE(packet->put(original[i]));
        } else {
            REQUIRE(packet->put(original[i]));
        }
    }

    REQUIRE(packet->send());

    for (auto& transmitter : transmitters) {
        REQUIRE(transmitter->_packets.size() == 1);
        auto& [ch, received] = transmitter->_packets[0];

        REQUIRE(ch == channel);

        CAPTURE(original);
        CAPTURE(received);
        REQUIRE(std::equal(original.begin(), original.begin() + capacity, received.begin(), received.end()));
    }
}
