#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <unordered_map>
#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <variant>

#include "linkTypes.h"


namespace jac {


/**
 * @brief A router that can route packets from multiple channel
 * connections to consumers on specific channels.
 */
class Router {
    std::unordered_map<uint8_t, std::reference_wrapper<Consumer>> _channelConsumers;
    std::function<void(int sender, uint8_t channel, std::span<const uint8_t> data)> _global;
    std::unordered_map<int, std::reference_wrapper<ChannelTransmitter>> _many;

    class MulticastPacket : public Packet {
    private:
        Router& _router;
        uint8_t _channel;
        size_t _maxSize;
        std::vector<uint8_t> _data;
        std::vector<int> _recipients;
    public:
        MulticastPacket(Router& router, uint8_t channel, std::vector<int> recipients) :
            _router(router),
            _channel(channel),
            _recipients(std::move(recipients))
        {
            _maxSize = _router.maxPacketSize(channel, _recipients);
            _data.reserve(_maxSize);
        }

        bool put(uint8_t c) override {
            if (_data.size() >= _maxSize) {
                return true;
            }
            _data.push_back(c);
            return _data.size() >= _maxSize;
        }

        size_t put(std::span<const uint8_t> data) override {
            size_t n = std::min(data.size(), _maxSize - _data.size());
            _data.insert(_data.end(), data.begin(), data.begin() + n);
            return n;
        }

        size_t space() const override {
            return _maxSize - _data.size();
        }

        bool send() override {
            for (auto& [id, transmitter] : _router._many) {
                if (!_recipients.empty() && std::find(_recipients.begin(), _recipients.end(), id) == _recipients.end()) {
                    continue;
                }
                auto packet = transmitter.get().buildPacket(_channel);
                auto _put = packet->put(std::span(_data.begin(), _data.end()));
                if (_put != _data.size()) {
                    return false;
                }
                packet->send();
            }
            return true;
        }
    };
public:
    /**
     * @brief A handle for receiving packets from a channel connection.
     */
    class Handle : public ChannelReceiver {
    private:
        Router* _router;
        int _id;
        Handle(Router& router, int id) : _router(&router), _id(id) {}
    public:
        Handle(const Handle&) = delete;
        Handle& operator=(const Handle&) = delete;

        Handle& operator=(Handle&& other) {
            _router = other._router;
            _id = other._id;
            other._router = nullptr;
            return *this;
        }
        Handle(Handle&& other) {
            *this = std::move(other);
        }
        ~Handle() {
            if (_router) {
                _router->_many.erase(_id);
            }
        }

        void processPacket(uint8_t channel, std::span<const uint8_t> data) override {
            auto it = _router->_channelConsumers.find(channel);
            if (it != _router->_channelConsumers.end()) {
                it->second.get().processPacket(_id, data);
            }
            if (_router->_global) {
                _router->_global(_id, channel, data);
            }
        }

        friend class Router;
    };

    Router() = default;
    Router(const Router&) = delete;
    Router(Router&&) = delete;
    Router& operator=(const Router&) = delete;
    Router& operator=(Router&&) = delete;

    /**
     * @brief Set global callback which is called whenever a packet is received on any channel and connection.
     *
     * @param callback the callback
     */
    void setGlobalCallback(std::function<void(int sender, uint8_t channel, std::span<const uint8_t> data)> callback) {
        _global = callback;
    }

    /**
     * @brief Get the maximum packet size for a channel and recipients.
     *
     * @param channel the channel
     * @param recipients the recipients
     * @return The maximum packet size
     */
    size_t maxPacketSize(uint8_t channel, std::vector<int> recipients) {
        size_t size = 0;
        bool first = true;

        for (auto& [id, transmitter] : _many) {
            if (!recipients.empty() && std::find(recipients.begin(), recipients.end(), id) == recipients.end()) {
                continue;
            }
            if (first) {
                size = transmitter.get().maxPacketSize();
                first = false;
            } else {
                size = std::min(size, transmitter.get().maxPacketSize());
            }
        }

        return size;
    }

    /**
     * @brief Build a packet for a channel and recipients.
     *
     * @param channel the channel
     * @param recipients the recipients
     * @return The packet
     */
    std::unique_ptr<Packet> buildPacket(uint8_t channel, std::vector<int> recipients) {
        if (recipients.size() == 1) {
            auto tx = _many.find(recipients[0]);
            if (tx == _many.end()) {
                return nullptr;
            }
            return tx->second.get().buildPacket(channel);
        }
        if (recipients.size() == 0 && _many.size() == 1) {
            return _many.begin()->second.get().buildPacket(channel);
        }
        return std::make_unique<MulticastPacket>(*this, channel, std::move(recipients));
    }

    /**
     * @brief Subscribe a connection transmitter to the router.
     * @note This allows router to send packets to the connection.
     * Reciever should be then bound to the returned handle.
     *
     * @param id id of the connection
     * @param tx the transmitter
     * @return The handle
     */
    Handle subscribeTx(int id, ChannelTransmitter& tx) {
        if (_many.find(id) != _many.end()) {
            throw std::runtime_error("id already subscribed");
        }

        _many.insert_or_assign(id, std::ref(tx));
        return Handle(*this, id);
    }

    /**
     * @brief Subscribe a channel to a consumer.
     * @note All packets received on the channel will be passed to the consumer.
     *
     * @param channel the channel
     * @param consumer the consumer
     */
    void subscribeChannel(uint8_t channel, Consumer& consumer) {
        if (_channelConsumers.find(channel) != _channelConsumers.end()) {
            throw std::runtime_error("channel already subscribed");
        }

        _channelConsumers.insert_or_assign(channel, std::ref(consumer));
    }
};


} // namespace jac
