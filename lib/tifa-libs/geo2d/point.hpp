#ifndef TIFALIBS_GEO2D_POINT_HPP
#define TIFALIBS_GEO2D_POINT_HPP

#include "tifa-libs/geo2d/point_class.hpp"

namespace tifa_libs::geo2d {
constexpr Point make_P_polar(data_t r, data_t theta) { return Point{r * std::cos(theta), r * std::sin(theta)}; }

// distance of two points (Euclidian)
constexpr data_t dist_PP(const Point &lhs, const Point &rhs) { return std::hypot(lhs.x - rhs.x, lhs.y - rhs.y); }
// distance of two points (Manhattan)
constexpr data_t dist_MaPP(const Point &lhs, const Point &rhs) { return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y); }
// distance of two points (Chebyshev)
constexpr data_t dist_ChPP(const Point &lhs, const Point &rhs) { return std::max(std::abs(lhs.x - rhs.x), std::abs(lhs.y - rhs.y)); }

// (p2 -p1) ^  (p3 -p1)
constexpr data_t cross(const Point &p1, const Point &p2, const Point &p3) { return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y); }
constexpr ptrdiff_t sgn_cross(const Point &p1, const Point &p2, const Point &p3) { return sgn(cross(p1, p2, p3)); }

// (p2 -p1) * (p3 -p1)
constexpr data_t dot(const Point &p1, const Point &p2, const Point &p3) { return (p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y); }
constexpr ptrdiff_t sgn_dot(const Point &p1, const Point &p2, const Point &p3) { return sgn(dot(p1, p2, p3)); }

//! containing endpoints
constexpr bool is_in_middle(Point a, Point m, Point b) { return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y); }

// clamp angle of two points
constexpr data_t ang_PP(const Point &p1, const Point &p2) { return std::atan2(p1 ^ p2, p1 * p2); }
// clamp angle of two points, result in [0,2 pi)
constexpr data_t ang2pi_PP(const Point &p1, const Point &p2) {
    data_t res = ang_PP(p1, p2);
    return is_negative(res) ? res + 2 * PI : res;
}

// min distance of a set of points
//! need to sort `vp` first by the ascending order of x
data_t min_dist_Ps(const cont_t<Point> &vp, ptrdiff_t l, ptrdiff_t r) {
    data_t ret = DATA_MAX;
    if (r - l <= 5) {
        for (ptrdiff_t i = l; i < r; ++i)
            for (ptrdiff_t j = l; j < i; ++j) ret = std::min(ret, dist_PP(vp[i], vp[j]));
        return ret;
    }
    ptrdiff_t mid = r - (r - l) / 2;
    ret = std::min(min_dist_Ps(vp, l, mid), min_dist_Ps(vp, mid, r));
    cont_t<Point> q;
    for (ptrdiff_t i = l; i < r; ++i)
        if (std::abs(vp[i].x - vp[mid].x) <= ret) q.push_back(vp[i]);
    std::stable_sort(q.begin(), q.end(), [](const Point &lhs, const Point &rhs) -> bool { return lhs.y < rhs.y; });
    for (ptrdiff_t i = 1; i < (ptrdiff_t)q.size(); ++i)
        for (ptrdiff_t j = i - 1; ~j && q[j].y >= q[i].y - ret; --j) ret = std::min(ret, dist_PP(q[i], q[j]));
    return ret;
}

// max number of points covered by a circle with radius @r
uint_data_t max_cover_Ps(const cont_t<Point> &vp, const data_t r) {
    if (is_negative(r)) return uint_data_t{0};
    if (is_zero(r)) return uint_data_t{1};
    const data_t diam = r * 2;
    uint_data_t ans = 1;
    cont_t<std::pair<data_t, int_data_t>> angles;
    data_t dist;
    for (size_t i = 0; i < vp.size(); ++i) {
        angles.clear();
        for (size_t j = 0; j < vp.size(); ++j) {
            if (i == j || is_greater(dist = dist_PP(vp[i], vp[j]), diam)) continue;
            data_t delta = std::acos(dist / diam), polar = ang2pi_PP(vp[i], vp[j]);
            angles.emplace_back(polar - delta, 1);
            angles.emplace_back(polar + delta, -1);
        }
        std::sort(angles.begin(), angles.end());
        uint_data_t sum = 0;
        for (size_t j = 0; i < angles.size(); ++j) ans = std::max(ans, sum += angles[i].second);
    }
    return ans;
}
}  // namespace tifa_libs::geo2d

#endif