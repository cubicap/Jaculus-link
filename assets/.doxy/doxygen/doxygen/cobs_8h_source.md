
# File cobs.h

[**File List**](files.md) **>** [**encoders**](dir_2a175438597ed609dba8ae6e9b56060c.md) **>** [**cobs.h**](cobs_8h.md)

[Go to the documentation of this file.](cobs_8h.md) 

```C++

#pragma once

#include <cstdint>
#include <array>
#include <span>
#include "../util/crc.h"
#include "encoderTypes.h"


namespace jac {


struct CobsEncoder {
private:
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

public:
    class Serializer {
        class DataFrame : private PacketStructure {
            size_t _dataSize = 0;
        public:
            size_t size() const {
                return _dataSize;
            }

            bool put(uint8_t c) {
                if (_dataSize < SIZE_DATA_MAX) {
                    buffer[OFFSET_DATA + _dataSize] = c;
                    _dataSize++;
                }
                return _dataSize == SIZE_DATA_MAX;
            }

            size_t put(std::span<const uint8_t> data) {
                size_t amount = std::min(data.size(), SIZE_DATA_MAX - _dataSize);
                std::copy(data.begin(), data.begin() + amount, buffer.begin() + OFFSET_DATA + _dataSize);
                _dataSize += amount;
                return amount;
            }

            std::span<const uint8_t> finalize(uint8_t channel) {
                size_t length = OFFSET_DATA + _dataSize + SIZE_CHECKSUM;
                size_t crcOffset = OFFSET_DATA + _dataSize;

                buffer[OFFSET_DELIMITER] = DELIMITER;
                buffer[OFFSET_LENGTH] = static_cast<uint8_t>(crcOffset + SIZE_CHECKSUM - OFFSET_COBS);
                buffer[OFFSET_COBS] = DELIMITER;
                buffer[OFFSET_CHANNEL] = channel;

                Crc16 crc16;
                size_t prevDelim = 2;

                for (size_t i = 3; i < length; i++) {
                    // crc
                    if (i >= OFFSET_CHANNEL && i < crcOffset) {
                        crc16.update(buffer[i]);
                    }
                    else if (i == crcOffset) {
                        buffer[crcOffset] = crc16.value() & 0xFF;
                        buffer[crcOffset + 1] = crc16.value() >> 8;
                    }

                    // cobs
                    if (buffer[i] == DELIMITER) {
                        buffer[prevDelim] = static_cast<uint8_t>(i - prevDelim);
                        prevDelim = i;
                    }
                }
                buffer[prevDelim] = static_cast<uint8_t>(length - prevDelim);

                return { buffer.data(), length };
            }
        };

    public:
        static size_t capacity() {
            return PacketStructure::SIZE_DATA_MAX;
        }

        static DataFrame buildDataFrame() {
            return DataFrame();
        }
    };

    class Packetizer : private PacketStructure {
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

        DecodeResult decode() {
            size_t frameLength = expectedLength();

            if (length < frameLength) {
                return { false, 0, {} };
            }

            Crc16 crc;
            size_t crcOffset = OFFSET_COBS + buffer[OFFSET_LENGTH] - SIZE_CHECKSUM;
            size_t nextDelimOff = 0;

            for (size_t i = 2; i < frameLength; i++) {
                if (nextDelimOff == 0) {
                    nextDelimOff = buffer[i];
                    buffer[i] = DELIMITER;
                }
                nextDelimOff--;

                if (i >= OFFSET_CHANNEL && i < crcOffset) {
                    crc.update(buffer[i]);
                }
            }

            uint16_t crcReceived = buffer[crcOffset] | (buffer[crcOffset + 1] << 8);

            reset();

            if (nextDelimOff != 0 || crc.value() != crcReceived) {
                return { false, 1, {} };
            }

            return {
                true,
                buffer[OFFSET_CHANNEL],
                std::span<const uint8_t>(buffer.begin() + OFFSET_DATA, buffer.begin() + crcOffset)
            };
        }
    };
};


} // namespace jac

```