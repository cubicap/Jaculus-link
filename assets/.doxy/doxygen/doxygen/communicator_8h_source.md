
# File communicator.h

[**File List**](files.md) **>** [**jac**](dir_256037ad7d0c306238e2bc4f945d341d.md) **>** [**link**](dir_c1e6982d0168263bc2c86cc40d5c26c8.md) **>** [**communicator.h**](communicator_8h.md)

[Go to the documentation of this file.](communicator_8h.md) 

```C++

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <set>
#include <span>
#include <vector>

#include "linkTypes.h"


namespace jac {


class OutputStreamCommunicator {
public:
    virtual bool put(uint8_t c) = 0;

    virtual size_t write(std::span<const uint8_t> data) = 0;

    virtual void setRecipients(std::vector<int> recipients) = 0;

    OutputStreamCommunicator() = default;
    OutputStreamCommunicator(const OutputStreamCommunicator&) = delete;
    OutputStreamCommunicator& operator=(const OutputStreamCommunicator&) = delete;
    virtual ~OutputStreamCommunicator() = default;
};


class InputStreamCommunicator {
public:
    virtual int get() = 0;

    virtual size_t read(std::span<uint8_t> data) = 0;

    virtual size_t available() = 0;

    virtual void filter(std::set<int> links) = 0;

    virtual void clear() = 0;

    virtual void cancelRead() = 0;

    InputStreamCommunicator() = default;
    InputStreamCommunicator(const InputStreamCommunicator&) = delete;
    InputStreamCommunicator& operator=(const InputStreamCommunicator&) = delete;
    virtual ~InputStreamCommunicator() = default;
};


class OutputPacketCommunicator {
public:
    virtual std::unique_ptr<Packet> buildPacket(std::vector<int> links) = 0;

    virtual size_t maxPacketSize(std::vector<int> links) const = 0;

    OutputPacketCommunicator() = default;
    OutputPacketCommunicator(const OutputPacketCommunicator&) = delete;
    OutputPacketCommunicator& operator=(const OutputPacketCommunicator&) = delete;
    virtual ~OutputPacketCommunicator() = default;
};


class InputPacketCommunicator {
public:
    virtual std::optional<std::pair<int, std::vector<uint8_t>>> get() = 0;

    virtual size_t available() = 0;

    virtual void clear() = 0;

    virtual void cancelRead() = 0;

    InputPacketCommunicator() = default;
    InputPacketCommunicator(const InputPacketCommunicator&) = delete;
    InputPacketCommunicator& operator=(const InputPacketCommunicator&) = delete;
    virtual ~InputPacketCommunicator() = default;
};


} // namespace jac

```