#ifndef TIFALIBS_GEO2D_UTIL_HPP
#define TIFALIBS_GEO2D_UTIL_HPP

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstddef>
#include <limits>
#include <numeric>
#include <vector>
#include <set>

namespace tifa_libs::geo2d {
using data_t = double;
using uint_data_t = uint64_t;
template <typename Tp>
using cont_t = std::vector<Tp>;
template <typename Tp>
using cont_set_t = std::set<Tp>;

constexpr data_t EPS = 1e-8;

// #define ENABLE_RELATIVE_ERR__

#if __cplusplus >= 201703l
using std::gcd, std::lcm;
#else
uint_data_t gcd(uint_data_t m, uint_data_t n) { return n == 0 ? m : gcd(n, m % n); }
uint_data_t lcm(uint_data_t m, uint_data_t n) { return m / gcd(m, n) * n; }
#endif

#ifdef ENABLE_RELATIVE_ERR__
#define DIFF__(x, y) (((x) - (y)) / std::abs(x))
#undef ENABLE_RELATIVE_ERR__
#else
#define DIFF__(x, y) ((x) - (y))
#endif

constexpr ptrdiff_t sgn(data_t lhs) { return lhs < -EPS ? -1 : lhs > EPS; }
constexpr bool is_negative(data_t x) { return sgn(x) & 2; }
constexpr bool is_zero(data_t x) { return !sgn(x); }
constexpr bool is_positive(data_t x) { return (sgn(x) + 1) & 2; }

constexpr ptrdiff_t comp(data_t lhs, data_t rhs) { return sgn(DIFF__(lhs, rhs)); }
constexpr bool is_less(data_t lhs, data_t rhs) { return is_negative(DIFF__(lhs, rhs)); }
constexpr bool is_equal(data_t lhs, data_t rhs) { return is_zero(DIFF__(lhs, rhs)); }
constexpr bool is_greater(data_t lhs, data_t rhs) { return is_positive(DIFF__(lhs, rhs)); }
#undef DIFF__

using int_data_t = std::make_signed<uint_data_t>::type;
const data_t PI = std::acos(data_t{-1});
constexpr data_t DATA_MAX = std::numeric_limits<data_t>::max();

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-conversion"
constexpr uint_data_t f2uint(data_t x) { return x + EPS; }
#pragma GCC diagnostic pop

//! containing endpoints
constexpr bool is_intersect(data_t l1, data_t r1, data_t l2, data_t r2) {
    if (l1 > r1) std::swap(l1, r1);
    if (l2 > r2) std::swap(l2, r2);
    return !(is_less(r1, l2) || is_less(r2, l1));
}
//! containing endpoints
constexpr bool is_in_middle(data_t l, data_t mid, data_t r) { return is_equal(l, mid) || is_equal(r, mid) || ((l < mid) ^ (r < mid)); }


// calculate area of triangle by the length of 3 edges
// numerical stability improved
constexpr data_t area_T_abc(data_t a, data_t b, data_t c) { return std::sqrt((a + (b + c)) * (c - (a - b)) * (c + (a - b)) * (a + (b - c))) / 4; }

#define TIFALIBS_GEO2D_FUNC_SCALA0__(self, name, ...) \
    constexpr auto name() const __VA_ARGS__;          \
    friend constexpr auto name(const self &lhs) { return lhs.name(); }

#define TIFALIBS_GEO2D_FUNC_iSCALA0__(self, name, ...) \
    auto name() const __VA_ARGS__;              \
    friend auto name(const self &lhs) { return lhs.name(); }

#define TIFALIBS_GEO2D_FUNC_SCALA1__(self, name, rhs_type1, rhs1, ...) \
    constexpr auto name(rhs_type1 rhs1) const __VA_ARGS__;             \
    friend constexpr auto name(const self &lhs, rhs_type1 rhs1) { return lhs.name(rhs1); }

#define TIFALIBS_GEO2D_FUNC_SELF0__(self, name, ...) \
    constexpr self &do_##name() __VA_ARGS__;         \
    friend constexpr self name(self lhs) { return lhs.do_##name(); }

#define TIFALIBS_GEO2D_FNUC_SELF1__(self, name, rhs_type1, rhs1, ...) \
    constexpr self &do_##name(rhs_type1 rhs1) __VA_ARGS__;            \
    friend constexpr self name(self lhs, rhs_type1 rhs1) { return lhs.do_##name(rhs1); }

#define TIFALIBS_GEO2D_FNUC_iSELF1__(self, name, rhs_type1, rhs1, ...) \
    self &do_##name(rhs_type1 rhs1) __VA_ARGS__;                \
    friend self name(self lhs, rhs_type1 rhs1) { return lhs.do_##name(rhs1); }
}  // namespace tifa_libs::geo2d

#endif