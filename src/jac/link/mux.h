#pragma once

#include "router.h"
#include "stream.h"
#include "linkTypes.h"

#include <deque>
#include <functional>
#include <memory>
#include <istream>
#include <ostream>
#include <span>
#include <mutex>
#include <vector>


namespace jac {


/**
 * @brief A multiplexer that creates multiple channels over a single stream connection.
 *
 * @tparam Packetizer Class implementing packetization of the protocol
 * @tparam Serializer Class implementing serialization of the protocol
 */
template<class Packetizer, class Serializer>
class Mux : public ChannelTransmitter {
public:
    enum class Error : int {
        INVALID_RECEIVE = 1,
        PACKETIZER = 2
    };
private:
    std::unique_ptr<ChannelReceiver> _receiver;
    std::unique_ptr<Duplex> _stream;

    Packetizer _packetizer;

    std::mutex _writeMutex;

    std::function<void(Error, std::vector<int>)> _errorHandler;

    class MuxPacket : public Packet {
        Mux& _mux;
        uint8_t _channel;
        Serializer::DataFrame _frame;
        bool sent = false;
    public:
        MuxPacket(Mux& mux, uint8_t channel) : _mux(mux), _channel(channel), _frame(Serializer::buildDataFrame()) {}

        bool put(uint8_t c) override {
            if (sent) {
                throw std::runtime_error("Packet already sent");
            }

            return _frame.put(c);
        }

        size_t put(std::span<const uint8_t> data) override {
            if (sent) {
                throw std::runtime_error("Packet already sent");
            }

            auto it = _frame.put(data);
            return it - data.begin();
        }

        size_t space() const override {
            return Serializer::capacity() - _frame.size();
        }

        bool send() override {
            if (sent) {
                throw std::runtime_error("Packet already sent");
            }
            auto data = _frame.finalize(_channel);

            std::lock_guard<std::mutex> lock(_mux._writeMutex);
            return _mux._stream->write(data) == data.size() && _mux._stream->flush();
        }
    };

public:
    Mux(std::unique_ptr<Duplex> stream) : _stream(std::move(stream)) {}
    Mux(const Mux&) = delete;
    Mux(Mux&&) = delete;

    /**
     * @brief Bind a receiver to this mux. Received packets will be forwarded to the receiver.
     *
     * @param receiver the receiver to bind
     */
    void bindRx(std::unique_ptr<ChannelReceiver> receiver) {
        // TODO: rewrite rx binding
        _receiver = std::move(receiver);
    }

    /**
     * @brief Receive and parse data from the stream. Any received packets will be
     * immediately forwarded to the bound receiver.
     */
    void receive() {
        int c;
        while ((c = _stream->get()) != EOF) {
            auto putRes = _packetizer.put(c);
            if (putRes > 0) {
                auto result = _packetizer.decode();
                if (result.valid) {
                    if (_receiver) {
                        _receiver->processPacket(result.channel, result.data);
                    }
                }
                else {
                    // handle invalid packet
                    if (_errorHandler) {
                        _errorHandler(Error::INVALID_RECEIVE, { putRes, result.channel });
                    }
                }
            }
            else if (putRes < 0) {
                // handle protocol error
                if (_errorHandler) {
                    _errorHandler(Error::PACKETIZER, { putRes });
                }
            }
        }
    }

    /**
     * @brief Build a packet for the given channel.
     *
     * @param channel the channel
     * @return The packet
     */
    std::unique_ptr<Packet> buildPacket(uint8_t channel) override {
        return std::make_unique<MuxPacket>(*this, channel);
    }

    /**
     * @brief Get the maximum packet size for this mux.
     *
     * @return The maximum packet size
     */
    size_t maxPacketSize() const override {
        return Serializer::capacity();
    }

    /**
     * @brief Set the error handler for this mux.
     *
     * @param handler the error handler
     */
    void setErrorHandler(std::function<void(Error, std::vector<int>)> handler) {
        _errorHandler = handler;
    }
};


} // namespace jac
