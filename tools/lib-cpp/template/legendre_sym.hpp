#pragma once

namespace my_template {
#include <cstddef>
#include <cstdint>
#include <numeric>

constexpr int32_t legendre_symbol(uint64_t a, uint64_t p) noexcept {
    if (a == 0) return 0;
    int32_t s = 1, _ctz = 0;
    while (a > 1) {
        if (a == p || a == 0 || p < 2) return 0;
        _ctz = __builtin_ctzll(a);
        if (((p - 1) & 7) && ((p + 1) & 7) && (_ctz & 1)) s = -s;
        if ((a >>= _ctz) == 1) break;
        if ((((p - 1) & 7) * (a - 1)) & 7) s = -s;
        a ^= p ^= a ^= p %= a;
    }
    return s;
}
} // namespace my_template
