#pragma once

#include <span>
#include <cstdint>
#include <memory>


namespace jac {


/**
 * @brief Interface for a consumer of packets.
 */
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


/**
 * @brief Interface for creation of packets.
 */
class Packet {
public:
    virtual bool put(uint8_t c) = 0;
    virtual size_t put(std::span<const uint8_t> data) = 0;
    virtual size_t space() const = 0;

    virtual bool send() = 0;
    virtual ~Packet() = default;
};


/**
 * @brief Interface that allows for creation and sending of packets on a channel connection.
 */
class ChannelTransmitter {
public:
    ChannelTransmitter() = default;
    ChannelTransmitter(const ChannelTransmitter&) = delete;
    ChannelTransmitter& operator=(const ChannelTransmitter&) = delete;
    ChannelTransmitter(ChannelTransmitter&&) = delete;
    ChannelTransmitter& operator=(ChannelTransmitter&&) = delete;

    /**
     * @brief Build a packet for the given channel.
     *
     * @param channel the channel
     * @return The packet
     */
    virtual std::unique_ptr<Packet> buildPacket(uint8_t channel) = 0;

    /**
     * @brief Get the maximum packet size for the given channel.
     *
     * @param channel the channel
     * @return The maximum packet size
     */
    virtual size_t maxPacketSize() const = 0;

    virtual ~ChannelTransmitter() = default;
};


/**
 * @brief Interface that allows for receiving and processing packets on channel connection.
 */
class ChannelReceiver {
public:
    ChannelReceiver() = default;
    ChannelReceiver(const ChannelReceiver&) = delete;
    ChannelReceiver& operator=(const ChannelReceiver&) = delete;
    ChannelReceiver(ChannelReceiver&&) = delete;
    ChannelReceiver& operator=(ChannelReceiver&&) = delete;

    /**
     * @brief Process a received packet on the given channel.
     *
     * @param channel the channel
     * @param data data of the packet
     */
    virtual void processPacket(uint8_t channel, std::span<const uint8_t> data) = 0;

    virtual ~ChannelReceiver() = default;
};


} // namespace jac
