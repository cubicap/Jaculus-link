#pragma once

#include <vector>
#include <cstddef>
#include <deque>
#include <memory>
#include <jac/link/linkTypes.h>

#define EQUAL_ITERABLE(a, b) { REQUIRE(std::vector(a.begin(), a.end()) == std::vector(b.begin(), b.end())); }

template <typename T>
auto rangeVector(T start, size_t count) {
    static_assert(std::is_integral_v<T>);
    std::vector<T> result;
    while (count > 0) {
        result.push_back(start);
        ++start;
        --count;
    }
    return result;
}


class BufferTransmitter : public ChannelTransmitter {
public:
    size_t _maxPacketSize;
    std::vector<std::tuple<uint8_t, std::vector<uint8_t>>> _packets;

    BufferTransmitter(size_t maxPacketSize) : _maxPacketSize(maxPacketSize) {}

    class BufferPacket : public Packet {
        BufferTransmitter& _buftx;
        uint8_t _channel;
        std::vector<uint8_t> _data;
    public:
        BufferPacket(BufferTransmitter& bfrtx, uint8_t channel) : _buftx(bfrtx), _channel(channel) {}

        bool put(uint8_t c) override {
            if (_data.size() >= _buftx._maxPacketSize) {
                return true;
            }
            _data.push_back(c);
            return _data.size() >= _buftx._maxPacketSize;
        }

        size_t put(std::span<const uint8_t> data) override {
            auto toCopy = std::min(space(), data.size());
            _data.insert(_data.end(), data.begin(), data.begin() + toCopy);
            return toCopy;
        }

        size_t space() const override {
            return _buftx._maxPacketSize - _data.size();
        }

        bool send() override {
            _buftx._packets.emplace_back(_channel, _data);
            return true;
        }
    };

    std::unique_ptr<Packet> buildPacket(uint8_t channel) override {
        return std::make_unique<BufferPacket>(*this, channel);
    }

    size_t maxPacketSize() const override {
        return _maxPacketSize;
    }
};


class BufferConsumer : public Consumer {
public:
    std::vector<std::tuple<int, std::vector<uint8_t>>> _packets;

    void processPacket(int sender, std::span<const uint8_t> data) override {
        _packets.emplace_back(sender, std::vector<uint8_t>(data.begin(), data.end()));
    }
};
