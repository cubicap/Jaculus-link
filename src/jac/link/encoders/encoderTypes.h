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
