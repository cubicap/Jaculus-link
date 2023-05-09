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
 * @brief A router that can route packets from multiple data links to
 * to consumers on specific channels.
 */
class Router {
    std::unordered_map<uint8_t, std::reference_wrapper<Consumer>> _channelConsumers;
    std::function<void(int linkId, uint8_t channel, std::span<const uint8_t> data)> _global;
    std::unordered_map<int, std::reference_wrapper<DataLinkTx>> _many;

    class MulticastPacket : public Packet {
    private:
        std::reference_wrapper<Router> _router;
        uint8_t _channel;
        size_t _maxSize;
        std::vector<uint8_t> _data;
        std::vector<int> _links;
    public:
        MulticastPacket(Router& router, uint8_t channel, std::vector<int> links):
            _router(router),
            _channel(channel),
            _links(std::move(links))
        {
            _maxSize = _router.get().maxPacketSize(channel, _links);
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
            for (auto& [id, transmitter] : _router.get()._many) {
                if (!_links.empty() && std::find(_links.begin(), _links.end(), id) == _links.end()) {
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
     * @brief A handle for receiving packets from a data link.
     */
    class Handle : public DataLinkRx {
    private:
        Router* _router;
        int _linkId;
        Handle(Router& router, int linkId) : _router(&router), _linkId(linkId) {}
    public:
        Handle(const Handle&) = delete;
        Handle& operator=(const Handle&) = delete;

        Handle& operator=(Handle&& other) {
            _router = other._router;
            _linkId = other._linkId;
            other._router = nullptr;
            return *this;
        }
        Handle(Handle&& other) {
            *this = std::move(other);
        }
        ~Handle() {
            if (_router) {
                _router->_many.erase(_linkId);
            }
        }

        void processPacket(uint8_t channel, std::span<const uint8_t> data) override {
            auto it = _router->_channelConsumers.find(channel);
            if (it != _router->_channelConsumers.end()) {
                it->second.get().processPacket(_linkId, data);
            }
            if (_router->_global) {
                _router->_global(_linkId, channel, data);
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
     * @brief Set global callback which is called whenever a packet is received on any channel and data link.
     *
     * @param callback the callback
     */
    void setGlobalCallback(std::function<void(int linkId, uint8_t channel, std::span<const uint8_t> data)> callback) {
        _global = callback;
    }

    /**
     * @brief Get the maximum packet size for a channel and data links.
     *
     * @param channel the channel
     * @param links the data links
     * @return The maximum packet size
     */
    size_t maxPacketSize(uint8_t channel, std::vector<int> links) {
        size_t size = 0;
        bool first = true;

        for (auto& [id, transmitter] : _many) {
            if (!links.empty() && std::find(links.begin(), links.end(), id) == links.end()) {
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
     * @brief Build a packet for a channel and data links.
     *
     * @param channel the channel
     * @param links the data links
     * @return The packet
     */
    std::unique_ptr<Packet> buildPacket(uint8_t channel, std::vector<int> links) {
        if (links.size() == 1) {
            auto tx = _many.find(links[0]);
            if (tx == _many.end()) {
                return nullptr;
            }
            return tx->second.get().buildPacket(channel);
        }
        if (links.size() == 0 && _many.size() == 1) {
            return _many.begin()->second.get().buildPacket(channel);
        }
        return std::make_unique<MulticastPacket>(*this, channel, std::move(links));
    }

    /**
     * @brief Subscribe a data link transmitter to the router.
     * @note This allows router to send packets to the data link id.
     * Reciever should be then bound to the returned handle.
     *
     * @param id id of the data link
     * @param tx the transmitter
     * @return The handle
     */
    Handle subscribeTx(int id, DataLinkTx& tx) {
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
