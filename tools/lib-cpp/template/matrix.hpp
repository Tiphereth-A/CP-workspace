#pragma once

namespace my_template {
#include <cstddef>
#include <functional>
#include <utility>

namespace Matrix {
#define _TRAITS(expression, __...) std::enable_if_t<expression, ##__>* = nullptr
#define _CONVERTIBLE(Tp, Up) std::is_convertible<Tp, Up>::value

namespace Matrix_helper {
struct normal_tag {};
struct euclid_tag {};

template <typename>
struct gauss_tag { using type = normal_tag; };

template <>
struct gauss_tag<euclid_tag> { using type = euclid_tag; };

template <typename Tp>
struct Zero final { static constexpr Tp value = 0; };

template <typename Tp>
struct One final { static constexpr Tp value = 1; };
} // namespace Matrix_helper
using namespace Matrix_helper;

template <class Tp, class Equal = std::equal_to<Tp>>
class matrix {
#define for_(i, begin, end, vals...) for (size_t i = (begin), ##vals; i < (end); ++i)
#define _for_row(i, vals...) for_(i, 0, this->get_row(), ##vals)
#define _for_col(i, vals...) for_(i, 0, this->get_col(), ##vals)
#define _for_each(i, j) _for_row(i) _for_col(j)
#define _square_matrix_needed \
    if (this->get_row() != this->get_col()) throw std::runtime_error("The matrix is not square matrix")

  public:
    using self = matrix<Tp, Equal>;
    using data_t = Tp;

  protected:
    constexpr friend std::ptrdiff_t _gauss(self& now) {
        size_t rk = 0;
        bool neg = false;
        for_(i, 0, std::min(now.get_row(), now.get_col()), now_row = 0) {
            now_row = rk;
            for_(j, now_row + 1, now.get_row()) if (std::abs(now.data(j, i)) > std::abs(now.data(now_row, i))) now_row = j;
            if (now.equ(now.data(now_row, i), now.get_zero())) continue;
            if (now_row != rk) {
                std::swap(now.mat[now_row], now.mat[rk]);
                neg ^= true;
            }
            for_(j, 0, now.get_row()) {
                if (j == rk) continue;
                data_t _ = now.data(j, i) / now.data(rk, i);
                now.data(j, i) = now.get_zero();
                for_(k, i + 1, now.get_col()) now.data(j, k) -= now.data(rk, k) * _;
            }
            ++rk;
        }
        return static_cast<std::ptrdiff_t>(neg ? -rk : rk);
    }

    constexpr friend std::ptrdiff_t _gauss_half(self& now) {
        size_t rk = 0;
        bool neg = false;
        for_(i, 0, std::min(now.get_row(), now.get_col()), now_row = 0) {
            now_row = rk;
            for_(j, now_row + 1, now.get_row()) if (std::abs(now.data(j, i)) > std::abs(now.data(now_row, i))) now_row = j;
            if (now.equ(now.data(now_row, i), now.get_zero())) continue;
            if (now_row != rk) {
                std::swap(now.mat[now_row], now.mat[rk]);
                neg ^= true;
            }
            for_(j, rk + 1, now.get_row()) {
                data_t _ = now.data(j, i) / now.data(rk, i);
                now.data(j, i) = now.get_zero();
                for_(k, i + 1, now.get_col()) now.data(j, k) -= now.data(rk, k) * _;
            }
            ++rk;
        }
        return static_cast<std::ptrdiff_t>(neg ? -rk : rk);
    }

    constexpr friend std::ptrdiff_t _gauss_euclid(self& now) {
        size_t rk = 0;
        bool neg = false;
        for_(i, 0, std::min(now.get_row(), now.get_col()), now_row = 0) {
            now_row = rk;
            for_(j, now_row + 1, now.get_row()) if (std::abs(now.data(j, i)) > std::abs(now.data(now_row, i))) now_row = j;
            if (now.equ(now.data(now_row, i), now.get_zero())) continue;
            if (now_row != rk) {
                std::swap(now.mat[now_row], now.mat[rk]);
                neg ^= true;
            }
            for_(j, 0, now.get_row()) {
                if (now.data(j, i) > now.data(i, i)) {
                    std::swap(now.mat[j], now.mat[i]);
                    neg ^= true;
                }
                while (!now.equ(now.data(i, i), now.get_zero())) {
                    std::ptrdiff_t _ = now.data(j, i) / now.data(i, i);
                    for_(k, i, now.get_row()) now.data(j, k) -= now.data(i, k) * data_t(_);
                    std::swap(now.mat[j], now.mat[i]);
                    neg ^= true;
                }
            }
            ++rk;
        }
        return static_cast<std::ptrdiff_t>(neg ? -rk : rk);
    }

    constexpr friend std::ptrdiff_t _gauss_half_euclid(self& now) {
        size_t rk = 0;
        bool neg = false;
        for_(i, 0, std::min(now.get_row(), now.get_col()), now_row = 0) {
            now_row = rk;
            for_(j, now_row + 1, now.get_row()) if (std::abs(now.data(j, i)) > std::abs(now.data(now_row, i))) now_row = j;
            if (now.equ(now.data(now_row, i), now.get_zero())) continue;
            if (now_row != rk) {
                std::swap(now.mat[now_row], now.mat[rk]);
                neg ^= true;
            }
            for_(j, rk + 1, now.get_row()) {
                if (now.data(j, i) > now.data(i, i)) {
                    std::swap(now.mat[j], now.mat[i]);
                    neg ^= true;
                }
                while (!now.equ(now.data(i, i), now.get_zero())) {
                    std::ptrdiff_t _ = now.data(j, i) / now.data(i, i);
                    for_(k, i, now.get_row()) now.data(j, k) -= now.data(i, k) * data_t(_);
                    std::swap(now.mat[j], now.mat[i]);
                    neg ^= true;
                }
            }
            ++rk;
        }
        return static_cast<std::ptrdiff_t>(neg ? -rk : rk);
    }

  public:
    matrix(const size_t& _row, const size_t& _col, const Equal& _equal = Equal()) : row(_row), col(_col), mat(_row, std::vector<data_t>(_col)), equ(_equal) {
        if (_row == 0 || _col == 0) throw std::logic_error("invalid parameters");
    }

    template <typename Up, _TRAITS(_CONVERTIBLE(Up, data_t))>
    matrix(const size_t& _row, const size_t& _col, Up&& scalar, const Equal& _equal = Equal()) : row(_row), col(_col), mat(_row, std::vector<data_t>(_col, scalar)), equ(_equal) {
        if (_row == 0 || _col == 0) throw std::logic_error("invalid parameters");
    }

    template <typename Up, _TRAITS(_CONVERTIBLE(Up, self&))>
    matrix(Up&& rhs) : row(std::forward<self>(rhs).get_row()), col(std::forward<self>(rhs).get_col()), mat(row), equ(std::forward<self>(rhs).equ) { _for_row(i) this->mat[i] = std::forward<self>(rhs).mat[i]; }

    template <typename Up, _TRAITS(_CONVERTIBLE(Up, self))>
    self& operator=(Up&& rhs) {
        _for_row(i) this->mat[i] = std::forward<self>(rhs).mat[i];
        return *this;
    }

    constexpr self& clear() {
        _for_each(i, j) this->data(i, j) = 0;
        return *this;
    }

    constexpr const size_t& get_row() const { return this->row; }
    constexpr const size_t& get_col() const { return this->col; }
    constexpr const data_t& get_zero() const { return this->zero; }
    constexpr const data_t& get_one() const { return this->one; }

    constexpr data_t& data(const size_t& r, const size_t& c) const { return const_cast<self* const>(this)->mat[r][c]; }
    constexpr data_t& data(const size_t& r, const size_t& c) { return this->mat[r][c]; }
    data_t& operator()(const size_t& r, const size_t& c) { return this->data(r, c); }

    template <typename Unary>
    constexpr self& transform_unary(Unary&& op) {
        _for_each(i, j) this->data(i, j) = op(this->data(i, j));
        return *this;
    }
    template <typename Unary>
    friend constexpr self calc_unary(const self& lhs, Unary&& op) { return self(lhs).transform_unary(op); }

    template <typename Binary>
    constexpr self& transform_binary(const self& rhs, Binary&& op) {
        _for_each(i, j) this->data(i, j) = op(this->data(i, j), rhs.data(i, j));
        return *this;
    }
    template <typename Binary>
    friend constexpr self calc_binary(const self& lhs, const self& rhs, Binary&& op) { return self(lhs).transform_binary(rhs, op); }

    constexpr friend std::ptrdiff_t gauss(self& now, normal_tag) { return _gauss(now); }
    constexpr friend std::ptrdiff_t gauss(self& now, euclid_tag) { return _gauss_euclid(now); }

    constexpr friend std::ptrdiff_t gauss_half(self& now, normal_tag) { return _gauss_half(now); }
    constexpr friend std::ptrdiff_t gauss_half(self& now, euclid_tag) { return _gauss_half_euclid(now); }

    constexpr self trans() {
        self ret(this->get_col(), this->get_row(), this->equ);
        _for_each(i, j) ret.data(j, i) = this->data(i, j);
        return ret;
    }

    constexpr size_t rank() const {
        self _ = self(*this);
        return std::abs(gauss_half(_, typename gauss_tag<data_t>::type()));
    }

    constexpr data_t det() const {
        _square_matrix_needed;

        self _ = self(*this);
        std::ptrdiff_t rk = gauss_half(_, typename gauss_tag<data_t>::type());
        if (static_cast<size_t>(std::abs(rk)) != this->get_row()) return this->get_zero();

        data_t ans(rk > 0 ? this->get_one() : -(this->get_one()));
        _for_row(i) ans *= this->data(i, i);
        return ans;
    }

    constexpr self inverse() const {
        _square_matrix_needed;

        self _(this->get_row(), this->get_row() * 2, this->equ);
        _for_each(i, j) _.data(i, j) = this->data(i, j);
        _for_each(i, j) _.data(i, j + this->get_row()) = (i == j ? 1 : 0);

        size_t rk = std::abs(gauss(_, typename gauss_tag<data_t>::type()));
        if (rk != this->get_row()) throw std::runtime_error("inverse not exist");

        _for_row(i) {
            const data_t& now = _.data(i, i);
            _for_col(j) _.data(i, j + this->get_row()) /= now;
        }

        self ret(this->get_row(), this->get_col(), this->equ);
        _for_each(i, j) ret.data(i, j) = _.data(i, j + this->get_row());
        return ret;
    }

    constexpr self& add(const self& rhs) { return this->transform_binary(rhs, std::plus<data_t>()); }
    constexpr self& minus(const self& rhs) { return this->transform_binary(rhs, std::minus<data_t>()); }
    constexpr self& multiply(const self& rhs) { return this->transform_binary(rhs, std::multiplies<data_t>()); }
    constexpr self& divide(const self& rhs) { return this->transform_binary(rhs, std::divides<data_t>()); }
    constexpr self& add(const data_t& scalar) {
        return this->transform_unary([&](const data_t& x) { return std::plus<data_t>()(x, scalar); });
    }
    constexpr self& minus(const data_t& scalar) {
        return this->transform_unary([&](const data_t& x) { return std::minus<data_t>()(x, scalar); });
    }
    constexpr self& multiply(const data_t& scalar) {
        return this->transform_unary([&](const data_t& x) { return std::multiplies<data_t>()(x, scalar); });
    }
    constexpr self& divide(const data_t& scalar) {
        return this->transform_unary([&](const data_t& x) { return std::divides<data_t>()(x, scalar); });
    }

    friend constexpr self& add(const self& lhs, const self& rhs) { return self(lhs).add(rhs); }
    friend constexpr self& minus(const self& lhs, const self& rhs) { return self(lhs).minus(rhs); }
    friend constexpr self& multiply(const self& lhs, const self& rhs) { return self(lhs).multiply(rhs); }
    friend constexpr self& divide(const self& lhs, const self& rhs) { return self(lhs).divide(rhs); }
    friend constexpr self& add(const self& lhs, const data_t& scalar) { return self(lhs).add(scalar); }
    friend constexpr self& minus(const self& lhs, const data_t& scalar) { return self(lhs).minus(scalar); }
    friend constexpr self& multiply(const self& lhs, const data_t& scalar) { return self(lhs).multiply(scalar); }
    friend constexpr self& divide(const self& lhs, const data_t& scalar) { return self(lhs).divide(scalar); }

    self operator*(const self& rhs) {
        if (this->get_col() != rhs.get_row()) throw std::logic_error("you can not multiple (" + std::to_string(this->get_row()) + "x" + std::to_string(this->get_col()) + ") matrix and (" + std::to_string(rhs.get_row()) + "x" + std::to_string(rhs.get_col()) + ") matrix");

        self ret(this->get_row(), rhs.get_col(), 0, this->equ);
        _for_row(i) _for_col(k) for_(j, 0, rhs.get_col()) ret.data(i, j) += this->data(i, k) * rhs.data(k, j);
        return ret;
    }

    self operator+() { return *this; }
    self operator-() { return self(*this).multiply(-1); }

    self& operator+=(const self& rhs) { return this->add(rhs); }
    self& operator-=(const self& rhs) { return this->minus(rhs); }
    self& operator*=(const self& rhs) { return *this = *this * rhs; }
    self& operator/=(const self& rhs) { return *this *= rhs.inverse(); }

    self operator+(const self& rhs) { return self(*this) += rhs; }
    self operator-(const self& rhs) { return self(*this) -= rhs; }
    self operator/(const self& rhs) { return self(*this) /= rhs; }

    bool operator==(const self& rhs) const {
        _for_each(i, j) if (!this->equ(this->data(i, j), rhs.data(i, j))) return false;
        return true;
    }
    bool operator!=(const self& rhs) const { return !(*this == rhs); }

    friend std::istream& operator>>(std::istream& is, self& x) {
        for_(i, 0, x.get_row()) for_(j, 0, x.get_col()) is >> x.data(i, j);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const self& x) {
        for_(i, 0, x.get_row()) for_(j, 0, x.get_col()) {
            os << x.data(i, j);
            if (i + 1 < x.get_row() || j + 1 < x.get_col()) os << (j + 1 == x.get_col() ? '\n' : ' ');
        }
        return os;
    }

  protected:
    const size_t row, col;
    std::vector<std::vector<Tp>> mat;
    Equal equ;
    static constexpr data_t zero = Zero<data_t>::value, one = One<data_t>::value;

#undef for_
#undef _for_row
#undef _for_col
#undef _for_each
#undef _square_matrix_needed
};

#undef _TRAITS
#undef _CONVERTIBLE
} // namespace Matrix
using Matrix::matrix;

template <>
struct Matrix::Matrix_helper::gauss_tag<int64_t> { using type = Matrix::Matrix_helper::euclid_tag; };

} // namespace my_template