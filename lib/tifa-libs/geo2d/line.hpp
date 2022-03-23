#ifndef TIFALIBS_GEO2D_LINE_HPP
#define TIFALIBS_GEO2D_LINE_HPP

#include "tifa-libs/geo2d/line_class.hpp"

namespace tifa_libs::geo2d {
// judge if two lines are intersected or not
constexpr bool is_ins_LL(const Line &l1, const Line &l2) { return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r)); }
// intersection point of two lines
constexpr Point ins_LL(const Line &l1, const Line &l2) {
    data_t a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
    return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}

// judge if two segments are intersected or not
//! containing endpoints
constexpr bool is_ins_SS(const Line &l1, const Line &l2) { return is_intersect(l1.l.x, l1.r.x, l2.l.x, l2.r.x) && is_intersect(l1.l.y, l1.r.y, l2.l.y, l2.r.y) && sgn_cross(l1.l, l1.r, l2.l) * sgn_cross(l1.l, l1.r, l2.r) <= 0 && sgn_cross(l2.l, l2.r, l1.l) * sgn_cross(l2.l, l2.r, l1.r) <= 0; }
// judge if two segments are intersected or not
//! NOT containing endpoints
constexpr bool is_ins_SS_strict(const Line &s1, const Line &s2) { return sgn_cross(s1.l, s1.r, s2.l) * sgn_cross(s1.l, s1.r, s2.r) < 0 && sgn_cross(s2.l, s2.r, s1.l) * sgn_cross(s2.l, s2.r, s1.r) < 0; }

// projection to a line
constexpr Point proj(const Line &l1, const Point &p) {
    Point dir = l1.direction();
    return l1.l + dir * (dir * (p - l1.l) / dir.norm());
}
// reflection about a line
constexpr Point reflect(const Line &l1, const Point &p) { return proj(l1, p) * 2 - p; }
constexpr bool is_on_same_L(const Point &p1, const Point &p2, const Point &p3) { return is_zero(cross(p1, p2, p3)); }

//! containing endpoints
constexpr bool is_on_S(const Line &s1, const Point &p) { return is_on_same_L(s1.l, s1.r, p) && is_in_middle(s1.l, p, s1.r); }
//! NOT containing endpoints
constexpr bool is_on_S_strict(const Line &s1, const Point &p) { return sgn_cross(s1.l, s1.r, p) == 0 && sgn((p - s1.l) * (s1.l - s1.r)) * sgn((p - s1.r) * (s1.l - s1.r)) < 0; }

// min dist_PP from a point to a line
constexpr data_t dist_PL(const Point &p, const Line &s1) {
    if (s1.l == s1.r) return dist_PP(s1.l, p);
    return dist_PP(p, proj(s1, p));
}
// min dist_PP from a point to another point which belongs to a segment
constexpr data_t dist_PS(const Point &p, const Line &s1) {
    if (s1.l == s1.r) return dist_PP(s1.l, p);
    Point h = proj(s1, p);
    if (is_in_middle(s1.l, h, s1.r)) return dist_PP(p, h);
    return std::min(dist_PP(s1.l, p), dist_PP(s1.r, p));
}
// dist_PP of two segments
constexpr data_t dist_SS(const Line &s1, const Line &s2) {
    if (is_ins_SS(s1, s2)) return 0;
    return std::min({dist_PS(s1.l, s2), dist_PS(s1.r, s2), dist_PS(s2.l, s1), dist_PS(s2.r, s1)});
}
}  // namespace tifa_libs::geo2d

#endif