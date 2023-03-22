#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <jac/link/util/crc.h>
#include <vector>
#include <span>
#include <tuple>
#include <cstdint>


TEST_CASE("crc16", "[crc]") {
    using sgn = typename std::tuple<int, std::vector<uint8_t>, uint16_t>;
    auto [id, data, expected] = GENERATE(
        sgn{ 1, { 0 }, 0},
        sgn{ 2, { 0, 0 }, 0},
        sgn{ 3, { 0, 0, 0 }, 0},
        sgn{ 4, { 1 }, 0xC0C1},
        sgn{ 5, { 1, 0 }, 0x9001},
        sgn{ 6, { 1, 0, 0 }, 0xC051},
        sgn{ 7, { 'a', 'b', 'c', 'd' }, 0x3997}
    );

    DYNAMIC_SECTION("crc16(" + std::to_string(id) + ")") {
        Crc16 crc;
        crc.update(std::span(data.data(), data.size()));
        REQUIRE(crc.value() == expected);
    }
}
