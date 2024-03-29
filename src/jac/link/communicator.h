#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <set>
#include <span>
#include <vector>

#include "linkTypes.h"


namespace jac {


/**
 * @brief Communicator interface that can be used send stream data.
 */
class OutputStreamCommunicator {
public:
    /**
     * @brief Put a single byte to the stream.
     *
     * @param c the byte to put
     * @return True if the byte was put successfully
     */
    virtual bool put(uint8_t c) = 0;

    /**
     * @brief Write a buffer to the stream.
     *
     * @param data the buffer to write
     * @return The number of bytes put
     */
    virtual size_t write(std::span<const uint8_t> data) = 0;

    /**
     * @brief Set the data links the stream should be sent to. Empty links for broadcast.
     *
     * @param recipients the data link ids
     */
    virtual void setRecipients(std::vector<int> recipients) = 0;

    OutputStreamCommunicator() = default;
    OutputStreamCommunicator(const OutputStreamCommunicator&) = delete;
    OutputStreamCommunicator& operator=(const OutputStreamCommunicator&) = delete;
    virtual ~OutputStreamCommunicator() = default;
};


/**
 * @brief Communicator interface that can be used to receive stream data.
 */
class InputStreamCommunicator {
public:
    /**
     * @brief Get a single byte from the stream.
     * @note This method blocks until data is available.
     *
     * @return the byte or -1 if no data is available
     */
    virtual int get() = 0;

    /**
     * @brief Read data from the stream.
     * @note This method blocks until data is available.
     *
     * @param data the buffer to read into
     * @return The number of bytes read
     */
    virtual size_t read(std::span<uint8_t> data) = 0;

    /**
     * @brief Get the number of bytes available to read.
     *
     * @return The number
     */
    virtual size_t available() = 0;

    /**
     * @brief Set filter to only receive data from the given data links. Empty links for any.
     *
     * @param links the data link ids
     */
    virtual void filter(std::set<int> links) = 0;

    /**
     * @brief Clear the buffer.
     */
    virtual void clear() = 0;

    /**
     * @brief Cancel any blocking read.
     */
    virtual void cancelRead() = 0;

    InputStreamCommunicator() = default;
    InputStreamCommunicator(const InputStreamCommunicator&) = delete;
    InputStreamCommunicator& operator=(const InputStreamCommunicator&) = delete;
    virtual ~InputStreamCommunicator() = default;
};


/**
 * @brief Communicator interface that can be used to send packets.
 */
class OutputPacketCommunicator {
public:
    /**
     * @brief Build a packet for the given data links.
     *
     * @param links the data link ids
     * @return The packet
     */
    virtual std::unique_ptr<Packet> buildPacket(std::vector<int> links) = 0;

    /**
     * @brief Get the maximum packet size for the given data links.
     *
     * @param links the data link ids
     * @return The maximum packet size
     */
    virtual size_t maxPacketSize(std::vector<int> links) const = 0;

    OutputPacketCommunicator() = default;
    OutputPacketCommunicator(const OutputPacketCommunicator&) = delete;
    OutputPacketCommunicator& operator=(const OutputPacketCommunicator&) = delete;
    virtual ~OutputPacketCommunicator() = default;
};


/**
 * @brief Communicator interface that can be used to receive packets.
 */
class InputPacketCommunicator {
public:
    /**
     * @brief Get the next packet.
     * @note This method blocks until a packet is available.
     *
     * @return The packet
     */
    virtual std::optional<std::pair<int, std::vector<uint8_t>>> get() = 0;

    /**
     * @brief Get the number of packets available to read.
     *
     * @return The number
     */
    virtual size_t available() = 0;

    /**
     * @brief Clear the buffer.
     */
    virtual void clear() = 0;

    /**
     * @brief Cancel any blocking read.
     */
    virtual void cancelRead() = 0;

    InputPacketCommunicator() = default;
    InputPacketCommunicator(const InputPacketCommunicator&) = delete;
    InputPacketCommunicator& operator=(const InputPacketCommunicator&) = delete;
    virtual ~InputPacketCommunicator() = default;
};


} // namespace jac
