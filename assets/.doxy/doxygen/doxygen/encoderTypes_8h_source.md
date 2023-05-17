
# File encoderTypes.h

[**File List**](files.md) **>** [**encoders**](dir_2a175438597ed609dba8ae6e9b56060c.md) **>** [**encoderTypes.h**](encoderTypes_8h.md)

[Go to the documentation of this file.](encoderTypes_8h.md) 

```C++

#pragma once

#include <cstdint>
#include <span>


namespace jac {


struct DecodeResult {
    bool valid;
    uint8_t channel;
    std::span<const uint8_t> data;
};


} // namespace jac

```