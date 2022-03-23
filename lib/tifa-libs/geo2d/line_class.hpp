#ifndef TIFALIBS_GEO2D_LINE_CLASS_HPP
#define TIFALIBS_GEO2D_LINE_CLASS_HPP

#include <iostream>

#include "tifa-libs/geo2d/util.hpp"
#include "tifa-libs/geo2d/point.hpp"

namespace tifa_libs::geo2d {
struct Line {
    Point l, r;
    Line() = default;
    constexpr Line(const Point &start_, const Point &end_): l(start_), r(end_) {}
    constexpr Line(const data_t &start_x, const data_t &start_y, const data_t &end_x, const data_t &end_y): l(start_x, start_y), r(end_x, end_y) {}
    friend std::istream &operator>>(std::istream &is, Line &rhs) { return is >> rhs.l >> rhs.r; }
    friend std::ostream &operator<<(std::ostream &os, const Line &rhs) { return os << rhs.l << ' ' << rhs.r; }

    constexpr Point direction() const { return r - l; }
    TIFALIBS_GEO2D_FUNC_SCALA1__(Line, is_parallel, const Line &, rhs, { return is_zero(direction() ^ rhs.direction()); })
    TIFALIBS_GEO2D_FUNC_SCALA1__(Line, is_same_dir, const Line &, rhs, { return is_parallel(rhs) && is_positive(direction() * rhs.direction()); })

    constexpr friend bool operator<(const Line &lhs, const Line &rhs) {
        if (lhs.is_same_dir(rhs)) return rhs.is_include_strict(lhs.l);
        auto vl = lhs.direction();
        auto vr = rhs.direction();
        if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
        return is_positive(vl ^ vr);
    }
    friend bool operator==(const Line &lhs, const Line &rhs) { return lhs.l == rhs.l && lhs.r == rhs.r; }

    TIFALIBS_GEO2D_FUNC_SCALA0__(Line, slope, { return (r.y - l.y) / (r.x - l.x); })
    TIFALIBS_GEO2D_FUNC_SCALA0__(Line, slope_inv, { return (r.x - l.x) / (r.y - l.y); })
    TIFALIBS_GEO2D_FUNC_SCALA0__(Line, intercept_v, { return r.y - r.x * slope(); })
    TIFALIBS_GEO2D_FUNC_SCALA0__(Line, intercept_h, { return r.x - r.y * slope_inv(); })

    TIFALIBS_GEO2D_FUNC_SCALA1__(Line, lerp_y, data_t, x, { return l.y + (x - l.x) * slope(); })
    TIFALIBS_GEO2D_FUNC_SCALA1__(Line, lerp_x, data_t, y, { return l.x + (y - l.y) * slope_inv(); })


    // half plane
    constexpr bool is_include_strict(const Point &p) const { return is_positive(cross(l, r, p)); }
    // half plane
    constexpr bool is_include(const Point &p) const { return !is_negative(cross(l, r, p)); }

    // translate @dist along the direction of half plane
    TIFALIBS_GEO2D_FNUC_SELF1__(Line, push, data_t, dist, {
        Point delta = direction().do_rot90().do_unit();
        delta *= dist;
        l += delta;
        r += delta;
        return *this;
    })
};
}  // namespace tifa_libs::geo2d

#endif