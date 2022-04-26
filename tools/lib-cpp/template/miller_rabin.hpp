#pragma once

#ifndef _DEBUG
#include "template/pow_mod.hpp"
#else
#include "pow_mod.hpp"
#endif


namespace my_template {
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace Primetest_miller_rabin {
using data_type = uint64_t;

using signed_data_t = std::make_signed_t<data_type>;
using unsigned_data_t = std::make_unsigned_t<data_type>;

// for int32
// constexpr unsigned_data_t bases[] = {2, 7, 61};

//for int64
constexpr unsigned_data_t bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

constexpr bool is_prime(unsigned_data_t n) {
    if (n <= 1) return false;
    for (unsigned_data_t a : bases)
        if (n == a) return true;
    if (n % 2 == 0) return false;

    unsigned_data_t d = n - 1;
    while (d % 2 == 0) d /= 2;
    for (unsigned_data_t a : bases) {
        unsigned_data_t t = d, y = pow_mod(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = mul_mod(y, y, n);
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) return false;
    }
    return true;
}
} // namespace Primetest_miller_rabin
using Primetest_miller_rabin::is_prime;

} // namespace my_template