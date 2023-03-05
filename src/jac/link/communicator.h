#pragma once

#include <cstdint>
#include <memory>
#include <set>
#include <span>
#include <vector>

#include "linkTypes.h"


class OutputStreamCommunicator {
public:
    virtual bool put(uint8_t c) = 0;
    virtual size_t write(std::span<const uint8_t> data) = 0;
    virtual void setRecipients(std::vector<int> recipients) = 0;  // empty recipients for broadcast
    virtual ~OutputStreamCommunicator() = default;
};

class BufferedInputStreamCommunicator {
public:
    virtual int get() = 0;
    virtual size_t read(std::span<uint8_t> data) = 0;
    virtual size_t available() = 0;
    virtual void filter(std::set<int> recipients) = 0;  // empty recipients for broadcast
    virtual ~BufferedInputStreamCommunicator() = default;
};


class OutputPacketCommunicator {
public:
    virtual std::unique_ptr<Packet> buildPacket(std::vector<int> recipients) = 0;
    virtual size_t maxPacketSize(std::vector<int> recipients) const = 0;

    virtual ~OutputPacketCommunicator() = default;
};


class BufferedInputPacketCommunicator {
public:
    virtual std::pair<int, std::vector<uint8_t>> get() = 0;
    virtual size_t available() = 0;
    virtual ~BufferedInputPacketCommunicator() = default;
};
