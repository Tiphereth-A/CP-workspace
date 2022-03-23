#pragma once

#ifndef _DEBUG
#include "template/mul_mod.hpp"
#else
#include "mul_mod.hpp"
#endif

namespace my_template {
#include <cmath>
#include <cstdint>

template <typename Tp, typename Up = uint64_t, std::enable_if_t<std::is_unsigned_v<Up>>* = nullptr>
constexpr Tp pow_mod(Tp a, Up b, const Up& mod) {
    Tp res(1);
    for (; b; b >>= 1, a = mul_mod(a, a, mod))
        if (b & 1) res = mul_mod(res, a, mod);
    return res;
}
} // namespace my_template
