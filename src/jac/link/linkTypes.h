#pragma once

#include <span>
#include <cstdint>
#include <memory>


class Consumer {
public:
    Consumer() = default;
    Consumer(const Consumer&) = delete;
    Consumer& operator=(const Consumer&) = delete;
    Consumer(Consumer&&) = delete;
    Consumer& operator=(Consumer&&) = delete;

    virtual void processPacket(int sender, std::span<const uint8_t> data) = 0;
    virtual ~Consumer() = default;
};


class Packet {
public:
    virtual bool put(uint8_t c) = 0;
    virtual size_t put(std::span<const uint8_t> data) = 0;
    virtual size_t space() const = 0;

    virtual bool send() = 0;
};

class ChannelTransmitter {
public:
    ChannelTransmitter() = default;
    ChannelTransmitter(const ChannelTransmitter&) = delete;
    ChannelTransmitter& operator=(const ChannelTransmitter&) = delete;
    ChannelTransmitter(ChannelTransmitter&&) = delete;
    ChannelTransmitter& operator=(ChannelTransmitter&&) = delete;

    virtual std::unique_ptr<Packet> buildPacket(uint8_t channel) = 0;
    virtual size_t maxPacketSize() const = 0;
};

class ChannelReceiver {
public:
    ChannelReceiver() = default;
    ChannelReceiver(const ChannelReceiver&) = delete;
    ChannelReceiver& operator=(const ChannelReceiver&) = delete;
    ChannelReceiver(ChannelReceiver&&) = delete;
    ChannelReceiver& operator=(ChannelReceiver&&) = delete;

    virtual void processPacket(uint8_t channel, std::span<const uint8_t> data) = 0;
};
