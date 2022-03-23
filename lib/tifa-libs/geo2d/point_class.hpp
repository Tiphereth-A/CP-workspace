#ifndef TIFALIBS_GEO2D_POINT_CLASS_HPP
#define TIFALIBS_GEO2D_POINT_CLASS_HPP

#include <iostream>

#include "tifa-libs/geo2d/util.hpp"

namespace tifa_libs::geo2d {
struct Point {
    data_t x, y;
    constexpr Point(data_t x = data_t{}, data_t y = data_t{}): x(x), y(y) {}

    friend std::istream &operator>>(std::istream &is, Point &rhs) { return is >> rhs.x >> rhs.y; }
    friend std::ostream &operator<<(std::ostream &os, const Point &rhs) { return os << rhs.x << ' ' << rhs.y; }

    constexpr Point &set_as_polar(data_t r, data_t theta) { return *this = {r * std::cos(theta), r * std::sin(theta)}; }
    // lhs * coord + rhs * (1 -coord)
    friend constexpr Point lerp(const Point &lhs, const Point &rhs, data_t coord) { return lhs * coord + rhs * (1 - coord); }


    friend constexpr Point mid_point(const Point &lhs, const Point &rhs) { return lerp(lhs, rhs, 0.5); }

#define SCALA_OP(op)                            \
    constexpr Point &operator op##=(data_t n) { \
        this->x op## = n;                       \
        this->y op## = n;                       \
        return *this;                           \
    }                                           \
    constexpr Point operator op(data_t n) const { return Point(*this) op## = n; }

    SCALA_OP(+)
    SCALA_OP(-)
    SCALA_OP(*)
    SCALA_OP(/)

#undef SCALA_OP

#define VEC_OP(op)                                      \
    constexpr Point &operator op##=(const Point &rhs) { \
        this->x op## = rhs.x;                           \
        this->y op## = rhs.y;                           \
        return *this;                                   \
    }                                                   \
    constexpr Point operator op(const Point &rhs) const { return Point(*this) op## = rhs; }

    VEC_OP(+)
    VEC_OP(-)

#undef VEC_OP

    constexpr Point operator-() const { return Point{-x, -y}; }
    constexpr bool operator<(const Point &rhs) const {
        auto c = comp(x, rhs.x);
        if (c) return c >> 1;
        return comp(y, rhs.y) >> 1;
    }
    constexpr bool operator==(const Point &rhs) const { return is_equal(x, rhs.x) && is_equal(y, rhs.y); }
    constexpr bool operator!=(const Point &rhs) const { return !(*this == rhs); }

    constexpr data_t operator*(const Point &rhs) const { return x * rhs.x + y * rhs.y; }
    constexpr data_t operator^(const Point &rhs) const { return x * rhs.y - y * rhs.x; }

    TIFALIBS_GEO2D_FUNC_SCALA0__(Point, arg, { return std::atan2(y, x); })
    // result in [0, 2pi)
    TIFALIBS_GEO2D_FUNC_SCALA0__(Point, arg2pi, { data_t tmp_ = arg(); return is_negative (tmp_) ? tmp_ + 2 * PI : tmp_; })
    TIFALIBS_GEO2D_FUNC_SCALA0__(Point, norm, { return x * x + y * y; })
    TIFALIBS_GEO2D_FUNC_SCALA0__(Point, abs, { return sqrt(norm()); })

    constexpr static int QUAD__[9] = {5, 6, 7, 4, 0, 0, 3, 2, 1};
    TIFALIBS_GEO2D_FUNC_SCALA0__(Point, quad, { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; })

    TIFALIBS_GEO2D_FUNC_SELF0__(Point, rot90, { data_t tmp = x; x = -y; y = tmp; return * this; })
    TIFALIBS_GEO2D_FUNC_SELF0__(Point, rot180, { x = -x; y = -y; return * this ; })
    TIFALIBS_GEO2D_FUNC_SELF0__(Point, rot270, { data_t tmp = y; y = -x; x = tmp; return * this; })
    TIFALIBS_GEO2D_FUNC_SELF0__(Point, unit, { return *this /= abs(); })

    TIFALIBS_GEO2D_FNUC_SELF1__(Point, rot, data_t, theta, {
        data_t _x = x, _y = y;
        x = _x * std::cos(theta) - _y * std::sin(theta);
        y = _x * std::sin(theta) + _y * std::cos(theta);
        return *this;
    })
};

}  // namespace tifa_libs::geo2d

#endif