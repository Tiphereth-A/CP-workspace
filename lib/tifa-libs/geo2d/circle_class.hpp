#ifndef TIFALIBS_GEO2D_CIRCLE_CLASS_HPP
#define TIFALIBS_GEO2D_CIRCLE_CLASS_HPP

#include <cassert>
#include <iostream>

#include "tifa-libs/geo2d/util.hpp"
#include "tifa-libs/geo2d/point_class.hpp"

namespace tifa_libs::geo2d {
struct Circle {
    Point o;
    data_t r;
    Circle() = default;
    constexpr Circle(const Point &c, data_t r): o(c), r(r) {}
    constexpr Circle(const data_t &c_x, const data_t &c_y, data_t r_): o(c_x, c_y), r(r_) {}
    friend std::istream &operator>>(std::istream &is, Circle &rhs) { return is >> rhs.o >> rhs.r; }
    friend std::ostream &operator<<(std::ostream &os, const Circle &rhs) { return os << rhs.o << ' ' << rhs.r; }
    friend bool operator==(const Circle &lhs, const Circle &rhs) { return lhs.o == rhs.o && lhs.r == rhs.r; }


    constexpr data_t area(data_t angle = PI * 2) const { return angle * r * r / 2; }
    constexpr data_t crown_area(data_t angle = PI * 2) const { return (angle - std::sin(angle)) * r * r / 2; }
    constexpr data_t arc(data_t angle = PI * 2) const { return angle * r; }
};
}  // namespace tifa_libs::geo2d

#endif