#pragma once

#ifndef _DEBUG
#include "template/miller_rabin.hpp"
#else
#include "miller_rabin.hpp"
#endif

namespace my_template {
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <random>
#include <utility>

namespace Pollard_rho {
using data_type = uint64_t;

using signed_data_t = std::make_signed_t<data_type>;
using unsigned_data_t = std::make_unsigned_t<data_type>;

std::default_random_engine e(time(nullptr));
std::uniform_int_distribution<data_type> u;
#define Rand(x) (u(e) % (x) + 1)

data_type pollard_rho(const data_type x, const data_type y) {
    data_type t = 0, k = 1;
    signed_data_t v0 = Rand(x - 1), v = v0;
    data_type d, s = 1;
    while (true) {
        v = (mul_mod(v, v, x) + y) % x;
        s = mul_mod(s, decltype(s)(std::abs(v - v0)), x);
        if (!(v ^ v0) || !s) return x;
        if (++t == k) {
            if ((d = std::gcd(s, x)) ^ 1) return d;
            v0 = v, k <<= 1;
        }
    }
}

void resolve(data_type x, data_type& ans) {
    if (!(x ^ 1) || x <= ans) return;
    if (is_prime(x)) {
        if (ans < x) ans = x;
        return;
    }
    data_type y = x;
    while ((y = pollard_rho(x, Rand(x))) == x)
        ;
    while (x % y == 0) x /= y;
    resolve(x, ans);
    resolve(y, ans);
}
data_type get_max_prime_divisor(data_type x) {
    data_type ans = 0;
    resolve(x, ans);
    return ans;
}
} // namespace Pollard_rho
using Pollard_rho::get_max_prime_divisor;
} // namespace my_template