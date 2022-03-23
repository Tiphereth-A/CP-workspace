#pragma once

namespace my_template {
#include <cstddef>
#include <utility>

#define _TRAITS(expression, __...) std::enable_if_t<expression, ##__>* = nullptr

template <typename Tp>
class mod_integer {
  public:
    using self = mod_integer<Tp>;
    using data_t = Tp;
    using mod_t = Tp;
    using common_t = std::common_type_t<data_t, mod_t>;
    using signed_common_t = std::make_signed_t<common_t>;
    using unsigned_common_t = std::make_unsigned_t<common_t>;

  protected:
    data_t num;
    mod_t mod;

  private:
    constexpr common_t gcd(common_t m, common_t n) const {
        while (n != 0) {
            common_t t = m % n;
            m = n;
            n = t;
        }
        return m;
    }

  public:
    mod_integer(const data_t& _num, const mod_t& _mod) noexcept : num(_num), mod(_mod) { this->safe_mod(); }

    template <typename Up, _TRAITS(std::is_convertible<Up, self&>::value)>
    mod_integer(Up&& rhs) noexcept : num(std::forward<self>(rhs).data()), mod(std::forward<self>(rhs).get_mod()) {}

    self& operator=(const data_t& num) noexcept {
        this->data() = num;
        return *this;
    }

    template <typename Up, _TRAITS(std::is_convertible<Up, self&>::value)>
    self& operator=(Up&& rhs) noexcept {
        this->data() = std::forward<self>(rhs).data();
        this->mod = std::forward<self>(rhs).get_mod();
        return *this;
    }

    operator data_t() { return this->data(); }

    constexpr self& no_check_mod() {
        this->num %= this->get_mod();
        return *this;
    }
    constexpr self& safe_mod() {
        if (this->no_check_mod().data() < 0) this->num += this->get_mod();
        return *this;
    }

    constexpr data_t& data() noexcept { return this->num; }
    constexpr data_t& data() const noexcept { return const_cast<self* const>(this)->num; }

    constexpr mod_t get_mod() const noexcept { return mod; }

    template <typename Unary>
    constexpr self& transform_unary_raw(Unary&& op) {
        this->data() = op(this->data());
        return *this;
    }
    template <typename Unary>
    constexpr self& transform_unary(Unary&& op) { return this->transform_unary_raw(std::move(op)).safe_mod(); }
    template <typename Binary>
    constexpr self& transform_binary_raw(const self& rhs, Binary&& op) {
        this->data() = op(this->data(), rhs.data());
        return *this;
    }
    template <typename Binary>
    constexpr self& transform_binary(const self& rhs, Binary&& op) { return this->transform_binary_raw(rhs, std::move(op)).safe_mod(); }

    template <typename Unary>
    friend constexpr self calc_unary_raw(const self& lhs, Unary&& op) { return self(lhs).transform_unary_raw(op); }
    template <typename Unary>
    friend constexpr self calc_unary(const self& lhs, Unary&& op) { return calc_unary_raw(lhs, std::move(op)).safe_mod(); }

    template <typename Binary>
    friend constexpr self calc_binary_raw(const self& lhs, const self& rhs, Binary&& op) { return self(lhs).transform_binary_raw(rhs, op); }
    template <typename Binary>
    friend constexpr self calc_binary(const self& lhs, const self& rhs, Binary&& op) { return calc_binary_raw(lhs, rhs, std::move(op)).safe_mod(); }

    constexpr self inverse() const {
        if (this->gcd(this->data(), this->get_mod()) != 1) throw std::runtime_error("inverse not exist");

        signed_common_t a = this->data(), b = this->get_mod();
        signed_common_t m0 = 0;

        for (signed_common_t q, _, m1 = 1; a;) {
            q = b / a;
            b -= a * q;
            m0 -= m1 * q;

            _ = b;
            b = a;
            a = _;
            _ = m0;
            m0 = m1;
            m1 = _;
        }

        return self(m0 + (m0 < 0 ? this->get_mod() / b : 0), this->get_mod());
    };

    self& operator++() {
        this->data()++;
        if (this->data() == this->get_mod()) this->data() = 0;
        return *this;
    }
    self& operator--() {
        if (this->data() == 0) this->data() = this->get_mod();
        this->data()--;
        return *this;
    }
    self operator++(int) {
        self ret = *this;
        ++*this;
        return ret;
    }
    self operator--(int) {
        self ret = *this;
        --*this;
        return ret;
    }

    self operator+() { return *this; }
    self operator-() { return self(this->get_mod() - this->data(), this->get_mod()); }

    self& operator+=(const self& rhs) { return this->transform_binary(rhs, std::plus<data_t>()); }
    self& operator-=(const self& rhs) { return this->transform_binary(rhs, std::minus<data_t>()); }
    self& operator*=(const self& rhs) { return this->transform_binary(rhs, std::multiplies<data_t>()); }
    self& operator/=(const self& rhs) { return this->transform_binary(rhs.inverse(), std::multiplies<data_t>()); }

    friend self operator+(const self& lhs, const self& rhs) { return self(lhs) += rhs; }
    friend self operator-(const self& lhs, const self& rhs) { return self(lhs) -= rhs; }
    friend self operator*(const self& lhs, const self& rhs) { return self(lhs) *= rhs; }
    friend self operator/(const self& lhs, const self& rhs) { return self(lhs) /= rhs; }

    friend bool operator==(const self& lhs, const self& rhs) { return lhs.data() == rhs.data(); }
    friend bool operator!=(const self& lhs, const self& rhs) { return lhs.data() != rhs.data(); }
    friend bool operator<(const self& lhs, const self& rhs) { return lhs.data() < rhs.data(); }
    friend bool operator>(const self& lhs, const self& rhs) { return lhs.data() > rhs.data(); }
    friend bool operator<=(const self& lhs, const self& rhs) { return lhs.data() <= rhs.data(); }
    friend bool operator>=(const self& lhs, const self& rhs) { return lhs.data() >= rhs.data(); }

    friend std::istream& operator>>(std::istream& is, self& x) {
        is >> x.data();
        x.safe_mod();
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const self& x) {
        os << x.data();
        return os;
    }
};

#undef _TRAITS
} // namespace my_template