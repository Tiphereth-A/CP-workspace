#pragma once

#ifndef _DEBUG
#include "template/legendre_sym.hpp"
#include "template/mul_mod.hpp"
#else
#include "legendre_sym.hpp"
#include "mul_mod.hpp"
#endif

namespace my_template {
#include <cstdint>
#include <optional>
#include <random>
#include <type_traits>

namespace quad_r {
using data_type = int64_t;

using signed_data_t = std::make_signed_t<data_type>;
using unsigned_data_t = std::make_unsigned_t<data_type>;

std::default_random_engine e(time(nullptr));

std::optional<data_type> quad_residue(const data_type& n, const unsigned_data_t& p) {
    if (n == 0 || n == 1 || n == p - 1) return n;
    if (legendre_symbol(n, p) != 1) return std::nullopt;

    std::uniform_int_distribution<unsigned_data_t> u(1, p - 1);
    data_type a = u(e);
    while (legendre_symbol((mul_mod(a, a, p) + (p - n)) % p, p) == 1) a = u(e);

    struct _gsint {
        using self = _gsint;

        data_type real, imag;
        const data_type i_sqr;
        const unsigned_data_t mod;

        explicit constexpr _gsint(const data_type& _r = data_type(), const data_type& _i = data_type(), const data_type& _ii = data_type(), const unsigned_data_t& _p = unsigned_data_t(1)) : real(_r), imag(_i), i_sqr(_ii), mod(_p) {}

        constexpr _gsint(const _gsint&) = default;

        constexpr self& operator*=(const self& rhs) {
            const data_type _ = (mul_mod(real, rhs.real, mod) + mul_mod(imag, rhs.imag, mod)) % mod;
            real = (mul_mod(real, rhs.real, mod) + mul_mod(mul_mod(i_sqr, imag, mod), rhs.imag, mod)) % mod;
            imag = _;
            return *this;
        }
    };

    return
        [](_gsint a, unsigned_data_t b) {
            _gsint res{1, 0, a.i_sqr, a.mod};
            for (; b; b >>= 1, a *= a)
                if (b & 1) res *= a;
            return res.real;
        }(_gsint{a, 1, (mul_mod(a, a, p) + (p - n)) % p, p}, (p + 1) / 2);
}
} // namespace quad_r
using quad_r::quad_residue;

} // namespace my_template