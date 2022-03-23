#pragma once

namespace my_template {
#include <cmath>
#include <cstdint>
#include <type_traits>

template <typename Tp = int64_t, typename Up = uint64_t, std::enable_if_t<(std::is_same_v<typename std::remove_cv<Tp>::type, int64_t> || std::is_same_v<typename std::remove_cv<Tp>::type, uint64_t>)&&std::is_unsigned_v<Up>>* = nullptr>
constexpr Tp mul_mod(Tp a, Tp b, const Up& mod) {
    Tp d = floorl(1.0l * a * b / mod + 0.5l), ret = a * b - d * mod;
    return ret < 0 ? ret + mod : ret;
}

template <typename Tp, typename Up, std::enable_if_t<std::is_integral_v<Tp> && !(std::is_same_v<typename std::remove_cv<Tp>::type, int64_t> || std::is_same_v<typename std::remove_cv<Tp>::type, uint64_t>) && std::is_unsigned_v<Up>>* = nullptr>
constexpr Tp mul_mod(Tp a, Tp b, const Up& mod) { return ((int64_t)a * b) % mod; }

//! unsafe
template <typename Tp, typename Up, std::enable_if_t<!std::is_integral_v<Tp> && std::is_unsigned_v<Up>>* = nullptr>
constexpr Tp mul_mod(Tp a, Tp b, const Up& mod) { return a * b % mod; }
} // namespace my_template
