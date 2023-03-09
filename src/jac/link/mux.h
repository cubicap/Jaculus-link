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


template<class Packetizer, class Serializer, class Stream>
class Mux : public ChannelTransmitter {
public:
    enum class Error : int {
        INVALID_RECEIVE = 1,
        PACKETIZER = 2
    };
private:
    ChannelReceiver* _receiver = nullptr;
    std::unique_ptr<Stream> _stream;

    Packetizer _packetizer;

    std::mutex _writeMutex;

    std::function<void(Error, std::vector<int>)> _errorHandler;
public:
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
            return _mux._stream->write(data) == data.size();
        }
    };

    Mux(std::unique_ptr<Stream> stream) : _stream(std::move(stream)) {}
    Mux(const Mux&) = delete;
    Mux(Mux&&) = delete;

    // TODO: rewrite rx binding
    void bindRx(ChannelReceiver& receiver) {
        _receiver = &receiver;
    }

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
                // handle cleared buffer
                if (_errorHandler) {
                    _errorHandler(Error::PACKETIZER, { putRes });
                }
            }
        }
    }

    std::unique_ptr<Packet> buildPacket(uint8_t channel) override {
        return std::make_unique<MuxPacket>(*this, channel);
    }

    size_t maxPacketSize() const override {
        return Serializer::capacity();
    }

    void setErrorHandler(std::function<void(Error, std::vector<int>)> handler) {
        _errorHandler = handler;
    }
};
