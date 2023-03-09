#pragma once

#include <cstdint>
#include <span>
#include <deque>
#include <memory>


class InputStream {
public:
    virtual int get() = 0;
    virtual size_t read(std::span<uint8_t> data) = 0;

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

    size_t write(std::span<const uint8_t> data) override {
        return _out->write(data);
    }

    bool flush() override {
        return _out->flush();
    }
};


class BufferStream : public InputStream, public OutputStream {
private:
    std::deque<uint8_t> _buffer;
public:
    BufferStream() {}

    int get() override {
        if (_buffer.empty()) {
            return EOF;
        }
        auto c = _buffer.front();
        _buffer.pop_front();
        return c;
    }

    size_t read(std::span<uint8_t> data) override {
        size_t i = 0;
        for (; i < data.size() && !_buffer.empty(); ++i) {
            data[i] = _buffer.front();
            _buffer.pop_front();
        }
        return i;
    }

    bool put(uint8_t c) override {
        _buffer.push_back(c);
        return true;
    }

    size_t write(std::span<const uint8_t> data) override {
        _buffer.insert(_buffer.end(), data.begin(), data.end());
        return data.size();
    }

    bool flush() override {
        return true;
    }
};
