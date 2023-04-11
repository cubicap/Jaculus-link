#pragma once

#include <cstdint>
#include <span>
#include <deque>
#include <memory>


namespace jac {


/**
 * @brief Interface for a binary input stream.
 */
class InputStream {
public:
    /**
     * @brief Get a single byte from the stream.
     * @note This method should not block.
     *
     * @return the byte or -1 if no data is available
     */
    virtual int get() = 0;

    /**
     * @brief Read data from the stream.
     * @note This method should not block.
     *
     * @param data the buffer to read into
     * @return The number of bytes read
     */
    virtual size_t read(std::span<uint8_t> data) = 0;

    virtual ~InputStream() = default;
};

/**
 * @brief Interface for a binary output stream.
 */
class OutputStream {
public:
    /**
     * @brief Write a single byte to the stream.
     * @note This method should not block.
     *
     * @param c the byte
     * @return true if the byte was written, false otherwise
     */
    virtual bool put(uint8_t c) = 0;

    /**
     * @brief Write a buffer to the stream.
     * @note This method should not block.
     *
     * @param data the buffer to write
     * @return The number of bytes written
     */
    virtual size_t write(std::span<const uint8_t> data) = 0;

    virtual bool flush() = 0;

    virtual ~OutputStream() = default;
};

/**
 * @brief Interface for an byte input/output stream.
 */
class Duplex : public InputStream, public OutputStream {};


/**
 * @brief A duplex stream that wraps an input and output stream.
 */
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


} // namespace jac
