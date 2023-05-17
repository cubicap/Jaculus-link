
# File crc.h

[**File List**](files.md) **>** [**jac**](dir_256037ad7d0c306238e2bc4f945d341d.md) **>** [**link**](dir_c1e6982d0168263bc2c86cc40d5c26c8.md) **>** [**util**](dir_29d605275cbfa1320720848587238697.md) **>** [**crc.h**](crc_8h.md)

[Go to the documentation of this file.](crc_8h.md) 

```C++

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

```