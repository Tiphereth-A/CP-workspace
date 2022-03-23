#pragma once

#ifndef _DEBUG
#include "template/pow_mod.hpp"
#else
#include "pow_mod.hpp"
#endif

namespace my_template {
#include <type_traits>

template <typename Tp, std::enable_if_t<std::is_integral_v<Tp>>* = nullptr>
class gauss_int {
  private:
    Tp _real;
    Tp _imag;

  public:
    using value_type = Tp;
    using self = gauss_int<Tp>;

    explicit constexpr gauss_int(const Tp& _r = Tp(), const Tp& _i = Tp()) : _real(_r), _imag(_i) {}

    template <typename Up>
    constexpr gauss_int(const gauss_int<Up>& z) : _real(z.real()), _imag(z.imag()) {}

    constexpr Tp real() const { return _real; }
    constexpr Tp imag() const { return _imag; }
    constexpr void real(Tp val) { _real = val; }
    constexpr void imag(Tp val) { _imag = val; }

    constexpr Tp norm() const { return inner_prod(*this, *this); }
    constexpr self&& conj() const { return gauss_int(_real, -_imag); }

    template <typename Up>
    friend constexpr std::common_type_t<Tp, Up> inner_prod(const self& x, const gauss_int<Up>& y) { return x.real() * y.real() + x.imag() * y.imag(); }
    template <typename Up>
    friend constexpr std::common_type_t<Tp, Up> outer_prod(const self& x, const gauss_int<Up>& y) { return x.real() * y.imag() - x.imag() * y.real(); }

    template <typename Up, std::enable_if_t<std::is_integral_v<Up>>* = nullptr>
    constexpr self& operator=(const Up& t) {
        _real = t;
        _imag = Tp();
        return *this;
    }

    template <typename Up, std::enable_if_t<std::is_integral_v<Up>>* = nullptr>
    constexpr self& operator+=(const Up& t) {
        _real += t;
        return *this;
    }
    template <typename Up, std::enable_if_t<std::is_integral_v<Up>>* = nullptr>
    constexpr self& operator-=(const Up& t) {
        _real -= t;
        return *this;
    }
    template <typename Up, std::enable_if_t<std::is_integral_v<Up>>* = nullptr>
    constexpr self& operator*=(const Up& t) {
        _real *= t;
        _imag *= t;
        return *this;
    }
    template <typename Up, std::enable_if_t<std::is_integral_v<Up>>* = nullptr>
    constexpr self& operator/=(const Up& t) {
        _real /= t;
        _imag /= t;
        return *this;
    }
    template <typename Up, std::enable_if_t<std::is_integral_v<Up>>* = nullptr>
    constexpr self& operator%=(const Up& t) {
        _real %= t;
        _imag %= t;
        return *this;
    }

    constexpr gauss_int& operator=(const gauss_int& z) = default;

    template <typename Up>
    constexpr self& operator=(const gauss_int<Up>& z) {
        _real = z.real();
        _imag = z.imag();
        return *this;
    }
    template <typename Up>
    constexpr self& operator+=(const gauss_int<Up>& z) {
        _real += z.real();
        _imag += z.imag();
        return *this;
    }
    template <typename Up>
    constexpr self& operator-=(const gauss_int<Up>& z) {
        _real -= z.real();
        _imag -= z.imag();
        return *this;
    }
    template <typename Up>
    constexpr self& operator*=(const gauss_int<Up>& z) {
        const Tp _ = _real * z.real() - _imag * z.imag();
        _imag = inner_prod(*this, z);
        _real = _;
        return *this;
    }
    template <typename Up>
    constexpr self& operator/=(const gauss_int<Up>& z) {
        const Tp _ = inner_prod(*this, z);
        _imag = outer_prod(z, *this) / z.norm();
        _real = _ / z.norm();
        return *this;
    }

    template <typename Up>
    constexpr self operator+(const Up& z) { return self(*this) += z; }
    template <typename Up>
    constexpr self operator-(const Up& z) { return self(*this) -= z; }
    template <typename Up>
    constexpr self operator*(const Up& z) { return self(*this) *= z; }
    template <typename Up>
    constexpr self operator/(const Up& z) { return self(*this) /= z; }
    template <typename Up>
    constexpr self operator%(const Up& z) { return self(*this) %= z; }
};


} // namespace my_template