#pragma once

#include <cstdint>
#include <span>
#include <iostream>

#include "stream.h"


class StdInputStream : public InputStream {
private:
    std::istream& _in;
public:
    StdInputStream(std::istream& in) : _in(in) {}
    int get() override {
        return _in.get();
    }

    size_t read(std::span<uint8_t> data) override {
        _in.read(reinterpret_cast<char*>(data.data()), data.size());
        return _in.gcount();
    }
};

class StdOutputStream : public OutputStream {
private:
    std::ostream& _out;
public:
    StdOutputStream(std::ostream& out) : _out(out) {}

    bool put(uint8_t c) override {
        _out.put(c);
        return true;
    }

    size_t write(std::span<const uint8_t> data) override {
        _out.write(reinterpret_cast<const char*>(data.data()), data.size());
        return data.size();  // TODO: return correct number
    }


    bool flush() override {
        _out.flush();
        return true;
    }
};
