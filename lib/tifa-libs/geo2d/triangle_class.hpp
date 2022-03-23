#ifndef TIFALIBS_GEO2D_TRIANGLE_CLASS_HPP
#define TIFALIBS_GEO2D_TRIANGLE_CLASS_HPP

#include <iostream>

#include "tifa-libs/geo2d/util.hpp"

#include "tifa-libs/geo2d/point.hpp"
#include "tifa-libs/geo2d/line.hpp"

namespace tifa_libs::geo2d {
struct Triangle {
    Point A, B, C;
    Triangle() = default;
    constexpr Triangle(const Point &a, const Point &b, const Point &c): A(a), B(b), C(c) {}
    constexpr Triangle(const data_t &a_x, const data_t &a_y, const data_t &b_x, const data_t &b_y, const data_t &c_x, const data_t &c_y): A(a_x, a_y), B(b_x, b_y), C(c_x, c_y) {}

    friend std::istream &operator>>(std::istream &is, Triangle &rhs) { return is >> rhs.A >> rhs.B >> rhs.C; }
    friend std::ostream &operator<<(std::ostream &os, const Triangle &rhs) { return os << rhs.A << ' ' << rhs.B << ' ' << rhs.C; }

    friend bool operator==(const Triangle &lhs, const Triangle &rhs) { return lhs.A == rhs.A && lhs.B == rhs.B && lhs.C == rhs.C; }


    constexpr data_t area() const { return std::abs(cross(A, B, C)) / 2; }

    constexpr Point average_w(data_t wA, data_t wB, data_t wC) const { return (A * wA + B * wB + C * wC) / (wA + wB + wC); }

    constexpr bool is_acute() const { return is_positive(dot(A, B, C)) && is_positive(dot(B, C, A)) && is_positive(dot(C, A, B)); }
    constexpr bool is_right() const { return is_zero(dot(A, B, C)) || is_zero(dot(B, C, A)) || is_zero(dot(C, A, B)); }
    constexpr bool is_obtuse() const { return is_negative(dot(A, B, C)) || is_negative(dot(B, C, A)) || is_negative(dot(C, A, B)); }

    // radius of inscribed circle
    constexpr data_t radius_I() const {
        data_t ab = dist_PP(A, B), bc = dist_PP(B, C), ca = dist_PP(C, A);
        return 2 * area() / (ab + bc + ca);
    }
    // radius of circumscribed circle
    constexpr data_t radius_O() const {
        data_t ab = dist_PP(A, B), bc = dist_PP(B, C), ca = dist_PP(C, A);
        return ab * bc * ca / (4 * area());
    }

    // incenter (X1)
    constexpr Point center_I() const { return average_w((B - C).abs(), (C - A).abs(), (A - B).abs()); }
    //! excenter of A
    constexpr Point center_E() const { return average_w(-((B - C).abs()), (C - A).abs(), (A - B).abs()); }
    // centroid (X2)
    constexpr Point center_G() const { return average_w(1, 1, 1); }
    // circumcenter (X3)
    constexpr Point center_O() const {
        Point p1 = mid_point(B, C), p2 = mid_point(C, A);
        return ins_LL({p1, p1 + (B - C).do_rot90()}, {p2, p2 + (C - A).do_rot90()});
    }
    // orthocenter (X4)
    constexpr Point center_H() const { return ins_LL({A, A + (B - C).do_rot90()}, {B, B + (C - A).do_rot90()}); }
    // 9-point center (X5)
    constexpr Point center_N() const { return mid_point(center_O(), center_H()); }
    // fermat center (X13)
    Point center_X() const {
        data_t s3 = sqrt(data_t{3}), r = radius_I(), R = radius_O(), s = ((A - B).abs() + (B - C).abs() + (C - A).abs()) / 2;
        return center_I() * (s3 * (r * r + 2 * r * R + s * s)) + center_O() * (-6 * r * (s3 * R - 2 * s)) + center_G() * (-2 * r * (s3 * r + 3 * s));
    }
};
}  // namespace tifa_libs::geo2d

#endif