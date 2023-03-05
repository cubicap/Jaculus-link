#pragma once

#include <cstdint>
#include <deque>
#include <memory>
#include <span>
#include <vector>

#include "communicator.h"
#include "router.h"


class TransparentOutputStreamCommunicator : public OutputStreamCommunicator {
    Router &_router;
    uint8_t _channel;
    std::vector<int> _recipients;
public:
    TransparentOutputStreamCommunicator(Router &router, uint8_t channel, std::vector<int> recipients)
            : _router(router), _channel(channel), _recipients(std::move(recipients)) {}
    bool put(uint8_t c) override {
        return write(std::span<const uint8_t>(&c, 1)) == 1;
    }

    size_t write(std::span<const uint8_t> data) override {
        auto it = data.begin();
        while (it != data.end()) {
            auto packet = _router.buildPacket(_channel, _recipients);
            auto size = packet->put(std::span<const uint8_t>(it, data.end()));
            if (size == 0) {
                return it - data.begin();
            }
            packet->send();
            it += size;
        }
        return data.size();
    }

    void setRecipients(std::vector<int> recipients) override {
        _recipients = std::move(recipients);
    }
};


class UnboundedBufferedInputStreamCommunicator : public BufferedInputStreamCommunicator, public Consumer {
    std::deque<std::vector<uint8_t>> _buffer;
    std::vector<uint8_t>::iterator _pos;
    std::set<int> _recipients;

    void next() {
        _pos++;
        if (_pos == _buffer.front().end()) {
            _buffer.pop_front();
            if (!_buffer.empty()) {
                _pos = _buffer.front().begin();
            }
        }
    }
public:
    UnboundedBufferedInputStreamCommunicator(std::set<int> recipients) : _recipients(std::move(recipients)) {}

    void processPacket(int sender, std::span<const uint8_t> data) override {
        if (!_recipients.empty() && _recipients.find(sender) == _recipients.end()) {
            return;
        }

        std::vector<uint8_t> v(data.begin(), data.end());
        _buffer.push_back(v);
        if (_buffer.size() == 1) {
            _pos = _buffer.front().begin();
        }
    }

    int get() override {
        if (_buffer.empty()) {
            return -1;
        }
        uint8_t c = *_pos;
        next();
        return c;
    }

    size_t read(std::span<uint8_t> buffer) override {
        size_t i;
        for (i = 0; i < buffer.size() && !_buffer.empty(); i++) {
            buffer[i] = *_pos;
            next();
        }
        return i;
    }

    size_t available() override {
        size_t size = 0;
        for (auto &v : _buffer) {
            size += v.size();
        }
        return size;
    }

    void filter(std::set<int> recipients) override {
        _recipients = std::move(recipients);
    }
};


class TransparentOutputPacketCommunicator : public OutputPacketCommunicator {
    Router &_router;
    uint8_t _channel;
public:
    TransparentOutputPacketCommunicator(Router &router, uint8_t channel) : _router(router), _channel(channel) {}
    std::unique_ptr<Packet> buildPacket(std::vector<int> recipients) override {
        return _router.buildPacket(_channel, recipients);
    }

    size_t maxPacketSize(std::vector<int> recipients) const override {
        return _router.maxPacketSize(_channel, recipients);
    }
};


class UnboundedBufferedInputPacketCommunicator : public BufferedInputPacketCommunicator, public Consumer {
    std::deque<std::pair<int, std::vector<uint8_t>>> _buffer;
public:
    UnboundedBufferedInputPacketCommunicator() {}

    void processPacket(int sender, std::span<const uint8_t> data) override {
        _buffer.push_back(std::make_pair(sender, std::vector<uint8_t>(data.begin(), data.end())));
    }

    std::pair<int, std::vector<uint8_t>> get() override {
        if (_buffer.empty()) {
            throw std::runtime_error("No data available");
        }
        auto p = _buffer.front();
        _buffer.pop_front();
        return p;
    }

    size_t available() override {
        return _buffer.size();
    }
};
