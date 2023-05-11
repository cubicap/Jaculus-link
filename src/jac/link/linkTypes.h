#pragma once

#include <span>
#include <cstdint>
#include <memory>


namespace jac {


/**
 * @brief Interface for a packet consumer.
 */
class Consumer {
public:
    Consumer() = default;
    Consumer(const Consumer&) = delete;
    Consumer& operator=(const Consumer&) = delete;
    Consumer(Consumer&&) = delete;
    Consumer& operator=(Consumer&&) = delete;

    virtual void processPacket(int linkId, std::span<const uint8_t> data) = 0;
    virtual ~Consumer() = default;
};


/**
 * @brief Interface for building packets.
 */
class Packet {
public:
    virtual bool put(uint8_t c) = 0;
    virtual size_t put(std::span<const uint8_t> data) = 0;
    virtual size_t space() const = 0;

    virtual bool send() = 0;

    Packet() = default;
    Packet(const Packet&) = delete;
    Packet& operator=(const Packet&) = delete;
    virtual ~Packet() = default;
};


/**
 * @brief Interface that allows for creation and sending of packets to a data link.
 */
class DataLinkTx {
public:
    DataLinkTx() = default;
    DataLinkTx(const DataLinkTx&) = delete;
    DataLinkTx& operator=(const DataLinkTx&) = delete;
    DataLinkTx(DataLinkTx&&) = delete;
    DataLinkTx& operator=(DataLinkTx&&) = delete;

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
};


/**
 * @brief Interface that allows for receiving and processing packets from a data link.
 */
class DataLinkRx {
public:
    DataLinkRx() = default;
    DataLinkRx(const DataLinkRx&) = delete;
    DataLinkRx& operator=(const DataLinkRx&) = delete;
    DataLinkRx(DataLinkRx&&) = delete;
    DataLinkRx& operator=(DataLinkRx&&) = delete;

    /**
     * @brief Process a received packet on the given channel.
     *
     * @param channel the channel
     * @param data data of the packet
     */
    virtual void processPacket(uint8_t channel, std::span<const uint8_t> data) = 0;

    virtual ~DataLinkRx() = default;
};


} // namespace jac
