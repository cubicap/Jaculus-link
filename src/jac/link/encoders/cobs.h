#pragma once

#include <cstdint>
#include <array>
#include <span>


struct DecodeResult {
    bool valid;
    uint8_t channel;
    std::span<const uint8_t> data;
};

struct PacketStructure {
    static constexpr uint8_t DELIMITER = 0x00;
    static constexpr size_t SIZE_CHECKSUM = 2;
    static constexpr size_t SIZE_LENGTH = 1;
    static constexpr size_t SIZE_CHANNEL = 1;

    static constexpr size_t OFFSET_DELIMITER = 0;
    static constexpr size_t OFFSET_LENGTH = 1;
    static constexpr size_t OFFSET_COBS = 2;
    static constexpr size_t OFFSET_CHANNEL = OFFSET_COBS + 1;
    static constexpr size_t OFFSET_DATA = OFFSET_CHANNEL + SIZE_CHANNEL;

    static constexpr size_t SIZE_DATA_MAX = 254 - SIZE_CHANNEL - SIZE_CHECKSUM;

    std::array<uint8_t, OFFSET_DATA + SIZE_DATA_MAX + SIZE_CHECKSUM> buffer;
};

class CobsSerializer : private PacketStructure {
    size_t _dataSize = 0;
public:
    size_t capacity() const {
        return SIZE_DATA_MAX;
    }

    size_t size() const {
        return _dataSize;
    }

    bool is_empty() const {
        return _dataSize == 0;
    }

    void reset() {
        _dataSize = 0;
    }

    bool put(uint8_t c) {
        if (_dataSize < SIZE_DATA_MAX) {
            buffer[OFFSET_DATA + _dataSize] = c;
            _dataSize++;
        }
        return _dataSize == SIZE_DATA_MAX;
    }

    auto put(std::span<const uint8_t> data) {
        size_t amount = std::min(data.size(), SIZE_DATA_MAX - _dataSize);
        std::copy(data.begin(), data.begin() + amount, buffer.begin() + OFFSET_DATA + _dataSize);
        _dataSize += amount;
        return data.begin() + amount;
    }

    std::span<const uint8_t> finalize(uint8_t channel) {
        size_t length = OFFSET_DATA + _dataSize + SIZE_CHECKSUM;
        size_t crcOffset = OFFSET_DATA + _dataSize;

        buffer[OFFSET_DELIMITER] = DELIMITER;
        buffer[OFFSET_LENGTH] = crcOffset + SIZE_CHECKSUM - OFFSET_COBS;
        buffer[OFFSET_COBS] = DELIMITER;
        buffer[OFFSET_CHANNEL] = channel;

        uint16_t crc = 0;
        size_t prevDelim = 2;

        for (size_t i = 3; i < length; i++) {
            // crc
            if (i >= OFFSET_CHANNEL && i < crcOffset) {
                // TODO: update crc
            }
            else if (i == crcOffset) {
                buffer[crcOffset] = crc & 0xFF;
                buffer[crcOffset + 1] = crc >> 8;
            }

            // cobs
            if (buffer[i] == DELIMITER) {
                buffer[prevDelim] = i - prevDelim;
                prevDelim = i;
            }
        }
        buffer[prevDelim] = length - prevDelim;
        reset();

        return { buffer.data(), length };
    }
};

class CobsPacketizer : private PacketStructure {
private:
    size_t length = 0;

    size_t expectedLength() const {
        if (length < OFFSET_LENGTH + SIZE_LENGTH) {
            return OFFSET_LENGTH + SIZE_LENGTH;
        }
        return OFFSET_LENGTH + SIZE_LENGTH + buffer[OFFSET_LENGTH];
    }
public:
    void reset() {
        length = 0;
    }

    int put(uint8_t c) {
        if (c == DELIMITER) {
            bool cleared = length != 0;
            buffer[0] = DELIMITER;
            length = 1;
            return cleared ? -1 : 0;
        }

        if (length == 0) {
            return -2;
        }

        if (length == expectedLength()) {
            return 2;
        }

        buffer[length] = c;
        length++;

        return length == expectedLength() ? 1 : 0;
    }

    // auto put(std::span<const uint8_t> data) {
    //     auto it = data.begin();
    //     if (length == expectedLength()) {
    //         return it;
    //     }

    //     for (; it != data.end(); ++it) {
    //         if (put(*it)) {
    //             return ++it;
    //         }
    //     }
    //     return data.end();
    // }

    DecodeResult decode() {
        size_t frameLength = expectedLength();

        if (length < frameLength) {
            return { false, 0, {} };
        }

        uint16_t crc = 0;
        size_t crcOffset = OFFSET_COBS + buffer[OFFSET_LENGTH] - SIZE_CHECKSUM;
        size_t nextDelimOff = 0;

        for (size_t i = 2; i < frameLength; i++) {
            if (nextDelimOff == 0) {
                nextDelimOff = buffer[i];
                buffer[i] = DELIMITER;
            }
            nextDelimOff--;

            if (i >= OFFSET_CHANNEL && i < crcOffset) {
                // TODO: update crc
            }
        }

        uint16_t crcReceived = buffer[crcOffset] | (buffer[crcOffset + 1] << 8);

        reset();

        if (nextDelimOff != 0 || crc != crcReceived) {
            return { false, 1, {} };
        }

        return {
            true,
            buffer[OFFSET_CHANNEL],
            std::span<const uint8_t>(buffer.begin() + OFFSET_DATA, buffer.begin() + crcOffset)
        };
    }
};
