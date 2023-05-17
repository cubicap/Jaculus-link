
# File stream.h

[**File List**](files.md) **>** [**jac**](dir_256037ad7d0c306238e2bc4f945d341d.md) **>** [**link**](dir_c1e6982d0168263bc2c86cc40d5c26c8.md) **>** [**stream.h**](stream_8h.md)

[Go to the documentation of this file.](stream_8h.md) 

```C++

#pragma once

#include <cstdint>
#include <deque>
#include <functional>
#include <memory>
#include <span>


namespace jac {


class InputStream {
public:
    virtual int get() = 0;

    virtual size_t read(std::span<uint8_t> data) = 0;

    virtual void onData(std::function<void(void)>) = 0;

    virtual ~InputStream() = default;
};

class OutputStream {
public:
    virtual bool put(uint8_t c) = 0;

    virtual size_t write(std::span<const uint8_t> data) = 0;

    virtual bool flush() = 0;

    virtual ~OutputStream() = default;
};

class Duplex : public InputStream, public OutputStream {};


class Duplexify : public Duplex {
private:
    std::unique_ptr<InputStream> _in;
    std::unique_ptr<OutputStream> _out;
public:
    Duplexify(std::unique_ptr<InputStream> in, std::unique_ptr<OutputStream> out):
        _in(std::move(in)),
        _out(std::move(out))
    {}

    int get() override {
        return _in->get();
    }

    size_t read(std::span<uint8_t> data) override {
        return _in->read(data);
    }

    bool put(uint8_t c) override {
        return _out->put(c);
    }

    void onData(std::function<void(void)> callback) override {
        _in->onData(callback);
    }

    size_t write(std::span<const uint8_t> data) override {
        return _out->write(data);
    }

    bool flush() override {
        return _out->flush();
    }
};


} // namespace jac

```