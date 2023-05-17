
# File linkTypes.h

[**File List**](files.md) **>** [**jac**](dir_256037ad7d0c306238e2bc4f945d341d.md) **>** [**link**](dir_c1e6982d0168263bc2c86cc40d5c26c8.md) **>** [**linkTypes.h**](linkTypes_8h.md)

[Go to the documentation of this file.](linkTypes_8h.md) 

```C++

#pragma once

#include <span>
#include <cstdint>
#include <memory>


namespace jac {


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


class DataLinkTx {
public:
    DataLinkTx() = default;
    DataLinkTx(const DataLinkTx&) = delete;
    DataLinkTx& operator=(const DataLinkTx&) = delete;
    DataLinkTx(DataLinkTx&&) = delete;
    DataLinkTx& operator=(DataLinkTx&&) = delete;

    virtual std::unique_ptr<Packet> buildPacket(uint8_t channel) = 0;

    virtual size_t maxPacketSize() const = 0;
};


class DataLinkRx {
public:
    DataLinkRx() = default;
    DataLinkRx(const DataLinkRx&) = delete;
    DataLinkRx& operator=(const DataLinkRx&) = delete;
    DataLinkRx(DataLinkRx&&) = delete;
    DataLinkRx& operator=(DataLinkRx&&) = delete;

    virtual void processPacket(uint8_t channel, std::span<const uint8_t> data) = 0;

    virtual ~DataLinkRx() = default;
};


} // namespace jac

```