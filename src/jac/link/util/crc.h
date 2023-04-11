#pragma once

#include <cstdint>
#include <span>


namespace jac {


class Crc16 {
private:
    static constexpr uint16_t POLYNOMIAL = 0xA001;
    uint16_t _crc;
public:
    Crc16() : _crc(0) {}

    void reset() {
        _crc = 0;
    }

    void update(uint8_t c) {
        _crc ^= c;
        for (int i = 0; i < 8; i++) {
            if (_crc & 1) {
                _crc = (_crc >> 1) ^ POLYNOMIAL;
            }
            else {
                _crc >>= 1;
            }
        }
    }

    void update(std::span<const uint8_t> data) {
        for (auto c : data) {
            update(c);
        }
    }

    uint16_t value() const {
        return _crc;
    }
};


} // namespace jac
