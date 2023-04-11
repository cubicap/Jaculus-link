#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <jac/link/routerCommunicator.h>
#include <cstddef>
#include <cmath>
#include <thread>
#include <array>

#include "util.h"


using namespace jac;


TEST_CASE("TransparentOutputStreamCommunicator", "[routerCommunicator]") {
    const size_t PACKET_SIZE = 256;
    const uint8_t CHANNEL = 0;

    Router router;
    BufferTransmitter transmitter(PACKET_SIZE);

    auto handle = router.subscribeTx(0, transmitter);

    TransparentOutputStreamCommunicator communicator(router, CHANNEL, {});

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>>;
    auto [comment, data] = GENERATE_COPY(
        sgn{ "empty", {} },
        sgn{ "one byte", { 0x01 } },
        sgn{ "two bytes", { 0x01, 0x02 } },
        sgn{ "one to full", rangeVector<uint8_t>(0x00, PACKET_SIZE - 1) },
        sgn{ "full", rangeVector<uint8_t>(0x00, PACKET_SIZE) },
        sgn{ "full + 1", rangeVector<uint8_t>(0x00, PACKET_SIZE + 1) },
        sgn{ "two packets", rangeVector<uint8_t>(0x00, PACKET_SIZE * 2) }
    );

    DYNAMIC_SECTION(comment) {
        communicator.write(std::span(data.begin(), data.end()));

        REQUIRE(transmitter._packets.size() == std::ceil(static_cast<double>(data.size()) / PACKET_SIZE));
        std::vector<uint8_t> received;
        for (auto& [channel, packet] : transmitter._packets) {
            REQUIRE(channel == CHANNEL);
            received.insert(received.end(), packet.begin(), packet.end());
        }

        REQUIRE(received == data);
    }
}


TEST_CASE("TransparentOutputStreamCommunicator - recipients", "[routerCommunicator]") {
    Router router;

    const std::vector<size_t> packetSizes = { 64, 256, 128 };
    size_t minPacketSize = *std::min_element(packetSizes.begin(), packetSizes.end());

    std::vector<std::unique_ptr<BufferTransmitter>> transmitters;
    std::vector<std::unique_ptr<Router::Handle>> handles;

    for (uint8_t i = 0; i < packetSizes.size(); i++) {
        transmitters.push_back(std::make_unique<BufferTransmitter>(packetSizes[i]));
        handles.push_back(std::make_unique<Router::Handle>(router.subscribeTx(i, *transmitters.back())));
    }

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>, std::vector<int>>;
    auto [comment, data, recipients] = GENERATE_COPY(
        sgn{ "single", rangeVector<uint8_t>(0x00, minPacketSize), { 0 } },
        sgn{ "two", rangeVector<uint8_t>(0x00, minPacketSize), { 0, 1 } },
        sgn{ "two 2", rangeVector<uint8_t>(0x00, minPacketSize), { 1, 2 } },
        sgn{ "two - out of order", rangeVector<uint8_t>(0x00, minPacketSize), { 1, 0 } },
        sgn{ "three", rangeVector<uint8_t>(0x00, 128), { 0, 1, 2 } },
        sgn{ "broadcast", rangeVector<uint8_t>(0x00, minPacketSize), {} }
    );

    DYNAMIC_SECTION(comment) {
        TransparentOutputStreamCommunicator communicator(router, 0, {});
        communicator.setRecipients(recipients);

        communicator.write(std::span(data.begin(), data.end()));

        for (size_t i = 0; i < transmitters.size(); i++) {
            auto& transmitter = *transmitters[i];

            CAPTURE(i);

            if (recipients.empty() || std::find(recipients.begin(), recipients.end(), i) != recipients.end()) {
                std::vector<uint8_t> received;
                for (auto& [channel, packet] : transmitter._packets) {
                    REQUIRE(channel == 0);
                    received.insert(received.end(), packet.begin(), packet.end());
                }

                REQUIRE(received == data);
            } else {
                REQUIRE(transmitter._packets.empty());
            }
        }
    }
}


TEST_CASE("UnboundedBufferedInputStreamCommunicator", "[routerCommunicator]") {
    const size_t PACKET_SIZE = 256;
    const uint8_t CHANNEL = 0;

    Router router;
    BufferTransmitter transmitter(PACKET_SIZE);

    auto handle = router.subscribeTx(0, transmitter);

    UnboundedBufferedInputStreamCommunicator communicator({});
    router.subscribeChannel(CHANNEL, communicator);

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>>;
    auto [comment, data] = GENERATE_COPY(
        sgn{ "empty", {} },
        sgn{ "one byte", { 0x01 } },
        sgn{ "two bytes", { 0x01, 0x02 } },
        sgn{ "one to full", rangeVector<uint8_t>(0x00, PACKET_SIZE - 1) },
        sgn{ "full", rangeVector<uint8_t>(0x00, PACKET_SIZE) },
        sgn{ "two packets", rangeVector<uint8_t>(0x00, PACKET_SIZE * 2) },
        sgn{ "three packets", rangeVector<uint8_t>(0x00, PACKET_SIZE * 3) }
    );

    DYNAMIC_SECTION(comment) {
        auto it = data.begin();
        while (it < data.end()) {
            handle.processPacket(0, std::span<const uint8_t>(it, std::min(it + PACKET_SIZE, data.end())));
            it += PACKET_SIZE;
        }

        REQUIRE(communicator.available() == data.size());

        std::vector<uint8_t> received;
        received.resize(communicator.available());

        auto it2 = received.begin();
        while (it2 < received.end()) {
            auto toRead = std::min(static_cast<size_t>(std::distance(it2, received.end())), PACKET_SIZE);
            REQUIRE(communicator.available() >= toRead);
            auto read = communicator.read(std::span(it2, toRead));
            REQUIRE(read == toRead);

            it2 += read;
        }

        REQUIRE(received == data);
    }
}


TEST_CASE("UnboundedBufferedInputStreamCommunicator - filter", "[routerCommunicator]") {
    const size_t PACKET_SIZE = 256;
    const uint8_t CHANNEL = 0;

    Router router;
    BufferTransmitter transmitter(PACKET_SIZE);

    auto handle = router.subscribeTx(0, transmitter);

    UnboundedBufferedInputStreamCommunicator communicator({});
    router.subscribeChannel(CHANNEL, communicator);

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>, std::set<int>>;
    auto [comment, data, filter] = GENERATE_COPY(
        sgn{ "single", rangeVector<uint8_t>(0x00, PACKET_SIZE), { 0 } },
        sgn{ "two", rangeVector<uint8_t>(0x00, PACKET_SIZE), { 0, 1 } },
        sgn{ "two 2", rangeVector<uint8_t>(0x00, PACKET_SIZE), { 1, 2 } },
        sgn{ "two - out of order", rangeVector<uint8_t>(0x00, PACKET_SIZE), { 1, 0 } },
        sgn{ "three", rangeVector<uint8_t>(0x00, PACKET_SIZE), { 0, 1, 2 } },
        sgn{ "broadcast", rangeVector<uint8_t>(0x00, PACKET_SIZE), {} }
    );

    DYNAMIC_SECTION(comment) {
        communicator.filter(filter);

        auto it = data.begin();
        while (it < data.end()) {
            handle.processPacket(0, std::span<const uint8_t>(it, std::min(it + PACKET_SIZE, data.end())));
            it += PACKET_SIZE;
        }

        if (filter.empty() || std::find(filter.begin(), filter.end(), 0) != filter.end()) {
            REQUIRE(communicator.available() == data.size());

            std::vector<uint8_t> received;

            while (communicator.available() > 0) {
                auto oldSize = received.size();
                received.resize(received.size() + communicator.available());

                communicator.read(std::span(received.begin() + oldSize, received.end()));
            }

            REQUIRE(received == data);
        } else {
            REQUIRE(communicator.available() == 0);
        }
    }
}


TEST_CASE("TransparentOutputPacketCommunicator", "[routerCommunicator]") {
    const size_t PACKET_SIZE = 256;
    const uint8_t CHANNEL = 0;

    Router router;
    BufferTransmitter transmitter1(PACKET_SIZE);
    BufferTransmitter transmitter2(PACKET_SIZE);
    BufferTransmitter transmitter3(PACKET_SIZE);

    auto handle1 = router.subscribeTx(0, transmitter1);
    auto handle2 = router.subscribeTx(1, transmitter2);
    auto handle3 = router.subscribeTx(2, transmitter3);

    TransparentOutputPacketCommunicator communicator(router, CHANNEL);

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>>;
    auto [comment, data] = GENERATE_COPY(
        sgn{ "empty", {} },
        sgn{ "one byte", { 0x01 } },
        sgn{ "two bytes", { 0x01, 0x02 } },
        sgn{ "one to full", rangeVector<uint8_t>(0x00, PACKET_SIZE - 1) },
        sgn{ "full", rangeVector<uint8_t>(0x00, PACKET_SIZE) },
        sgn{ "two packets", rangeVector<uint8_t>(0x00, PACKET_SIZE * 2) },
        sgn{ "three packets", rangeVector<uint8_t>(0x00, PACKET_SIZE * 3) }
    );

    DYNAMIC_SECTION("singlecast " + comment) {
        auto packet = communicator.buildPacket({0});
        auto sent = packet->put(std::span(data.begin(), data.end()));
        packet->send();

        REQUIRE(sent == std::min(data.size(), PACKET_SIZE));
        REQUIRE(transmitter1._packets.size() == 1);
        auto& [channel, packetData] = transmitter1._packets[0];
        REQUIRE(channel == CHANNEL);
        REQUIRE(packetData == std::vector<uint8_t>(data.begin(), data.begin() + sent));
    }

    DYNAMIC_SECTION("multicast " + comment) {
        auto packet = communicator.buildPacket({0, 1});
        auto sent = packet->put(std::span(data.begin(), data.end()));
        packet->send();

        REQUIRE(sent == std::min(data.size(), PACKET_SIZE));

        for (auto tx : {&transmitter1, &transmitter2}) {
            REQUIRE(tx->_packets.size() == 1);
            auto& [channel, packetData] = tx->_packets[0];
            REQUIRE(channel == CHANNEL);
            REQUIRE(packetData == std::vector<uint8_t>(data.begin(), data.begin() + sent));
        }

        REQUIRE(transmitter3._packets.size() == 0);
    }

    DYNAMIC_SECTION("broadcast " + comment) {
        auto packet = communicator.buildPacket({});
        auto sent = packet->put(std::span(data.begin(), data.end()));
        packet->send();

        REQUIRE(sent == std::min(data.size(), PACKET_SIZE));

        for (auto tx : {&transmitter1, &transmitter2, &transmitter3}) {
            REQUIRE(tx->_packets.size() == 1);
            auto& [channel, packetData] = tx->_packets[0];
            REQUIRE(channel == CHANNEL);
            REQUIRE(packetData == std::vector<uint8_t>(data.begin(), data.begin() + sent));
        }
    }
}


TEST_CASE("UnboundedBufferedInputPacketCommunicator", "[routerCommunicator]") {
    const size_t PACKET_SIZE = 256;
    const uint8_t CHANNEL = 0;

    Router router;
    BufferTransmitter transmitter(PACKET_SIZE);

    auto handle = router.subscribeTx(0, transmitter);

    UnboundedBufferedInputPacketCommunicator communicator;
    router.subscribeChannel(CHANNEL, communicator);

    using sgn = typename std::tuple<std::string, std::vector<uint8_t>>;
    auto [comment, data] = GENERATE_COPY(
        sgn{ "empty", {} },
        sgn{ "one byte", { 0x01 } },
        sgn{ "two bytes", { 0x01, 0x02 } },
        sgn{ "one to full", rangeVector<uint8_t>(0x00, PACKET_SIZE - 1) },
        sgn{ "full", rangeVector<uint8_t>(0x00, PACKET_SIZE) },
        sgn{ "two packets", rangeVector<uint8_t>(0x00, PACKET_SIZE * 2) },
        sgn{ "three packets", rangeVector<uint8_t>(0x00, PACKET_SIZE * 3) }
    );

    DYNAMIC_SECTION(comment) {
        std::vector<std::span<const uint8_t>> packets;

        auto it = data.begin();
        while (it < data.end()) {
            auto packetData = std::span<const uint8_t>(it, std::min(it + PACKET_SIZE, data.end()));
            packets.push_back(packetData);
            handle.processPacket(0, packetData);
            it += PACKET_SIZE;
        }

        REQUIRE(communicator.available() == packets.size());

        for (auto& packet : packets) {
            auto [sender, received] = *communicator.get();
            REQUIRE(sender == 0);
            EQUAL_ITERABLE(received, packet);
        }

        REQUIRE(communicator.available() == 0);
    }
}


TEST_CASE("Multithread UnboundedBufferedInputStreamCommunicator", "[routerCommunicator]") {
    const size_t PACKET_SIZE = 256;
    const uint8_t CHANNEL = 0;

    Router router;
    BufferTransmitter transmitter(PACKET_SIZE);

    auto handle = router.subscribeTx(0, transmitter);

    UnboundedBufferedInputStreamCommunicator communicator({});
    router.subscribeChannel(CHANNEL, communicator);

    std::vector<std::vector<uint8_t>> packets;
    for (size_t i = 0; i < 100; i++) {
        packets.push_back(rangeVector<uint8_t>('a', PACKET_SIZE));
    }

    std::vector<uint8_t> expected;
    for (auto& packet : packets) {
        expected.insert(expected.end(), packet.begin(), packet.end());
    }
    std::vector<uint8_t> received;

    std::thread rxThread([&] {
        while (received.size() < expected.size()) {
            std::array<uint8_t, 512> buffer;
            auto read = communicator.read(buffer);
            received.insert(received.end(), buffer.begin(), buffer.begin() + read);
        }
    });

    for (auto& packet : packets) {
        handle.processPacket(0, std::span<const uint8_t>(packet.data(), packet.size()));
    }

    rxThread.join();

    REQUIRE(received == expected);
}


TEST_CASE("Multithread UnboundedBufferedInputStreamCommunicator - cancelRead", "[routerCommunicator]") {
    const size_t PACKET_SIZE = 256;
    const uint8_t CHANNEL = 0;

    Router router;
    BufferTransmitter transmitter(PACKET_SIZE);

    auto handle = router.subscribeTx(0, transmitter);

    UnboundedBufferedInputStreamCommunicator communicator({});
    router.subscribeChannel(CHANNEL, communicator);

    bool running = true;

    std::thread rxThread([&] {
        std::array<uint8_t, 512> buffer;
        auto read = communicator.read(buffer);
        REQUIRE(read == 0);
        running = false;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    REQUIRE(running);
    communicator.cancelRead();
    rxThread.join();
    REQUIRE(!running);

    REQUIRE(communicator.available() == 0);
}


TEST_CASE("Multithread UnboundedBufferedInputPacketCommunicator", "[routerCommunicator]") {
    const size_t PACKET_SIZE = 256;
    const uint8_t CHANNEL = 0;

    Router router;
    BufferTransmitter transmitter(PACKET_SIZE);

    auto handle = router.subscribeTx(0, transmitter);

    UnboundedBufferedInputPacketCommunicator communicator;
    router.subscribeChannel(CHANNEL, communicator);

    std::vector<std::vector<uint8_t>> packets;
    for (uint8_t i = 0; i < 100; i++) {
        packets.push_back(rangeVector<uint8_t>(i, PACKET_SIZE));
    }

    std::vector<std::vector<uint8_t>> received;

    std::thread rxThread([&] {
        uint8_t count = 0;
        while (received.size() < packets.size()) {
            auto [sender, packet] = *communicator.get();
            REQUIRE(sender == 0);
            REQUIRE(packet[0] == count);
            count++;
            received.push_back(std::vector<uint8_t>(packet.begin(), packet.end()));
        }
    });

    for (size_t i = 0; i < packets.size(); i++) {
        handle.processPacket(0, std::span<const uint8_t>(packets[i].data(), packets[i].size()));
    }

    rxThread.join();

    REQUIRE(received == packets);
}


TEST_CASE("Multithread UnboundedBufferedInputPacketCommunicator - cancelRead", "[routerCommunicator]") {
    const size_t PACKET_SIZE = 256;
    const uint8_t CHANNEL = 0;

    Router router;
    BufferTransmitter transmitter(PACKET_SIZE);

    auto handle = router.subscribeTx(0, transmitter);

    UnboundedBufferedInputPacketCommunicator communicator;
    router.subscribeChannel(CHANNEL, communicator);

    bool running = true;

    std::thread rxThread([&] {
        REQUIRE(communicator.get() == make_pair(0, std::vector<uint8_t>()));
        REQUIRE(communicator.get() == std::nullopt);
        running = false;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    communicator.processPacket(0, std::span<const uint8_t>());

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    REQUIRE(running);
    communicator.cancelRead();
    rxThread.join();
    REQUIRE(!running);

    REQUIRE(communicator.available() == 0);
}
