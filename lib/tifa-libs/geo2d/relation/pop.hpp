#ifndef TIFALIBS_GEO2D_RELATION_POP_HPP
#define TIFALIBS_GEO2D_RELATION_POP_HPP

#include "tifa-libs/geo2d/util.hpp"
#include "tifa-libs/geo2d/cvh_class.hpp"

namespace tifa_libs::geo2d {
// relation between polygon/convex hull and point
enum RELA_PoP {
    outside_pop,
    onborder_pop,
    onendpoint_pop,
    inside_pop
};

RELA_PoP relation_PoP(const Polygon &poly, const Point &p) {
    for (auto &&now : poly.vs)
        if (now == p) return RELA_PoP::onendpoint_pop;
    bool result = false;
    for (size_t i = 0; i < poly.vs.size(); ++i) {
        Point now_p = poly.vs[i], next_p = poly.vs[poly.next(i)];
        if (is_on_S({now_p, next_p}, p)) return RELA_PoP::onborder_pop;
        if (!is_greater(now_p.y, next_p.y)) std::swap(now_p, next_p);
        if (is_greater(p.y, now_p.y) || !is_greater(p.y, next_p.y)) continue;
        result ^= sgn_cross(p, now_p, next_p) > 0;
    }
    return result ? RELA_PoP::inside_pop : RELA_PoP::outside_pop;
}

RELA_PoP relation_CvhP(const ConvexHull &cvh, const Point &p) {
    for (auto &&now : cvh.vs)
        if (now == p) return RELA_PoP::onendpoint_pop;
    size_t sz = cvh.vs.size();
    for (size_t i = 0; i < sz; ++i)
        if (is_on_S({cvh.vs[i], cvh.vs[cvh.next(i)]}, p)) return RELA_PoP::onborder_pop;
    if (sz < 3) return RELA_PoP::outside_pop;
    if (is_positive(cross(cvh.vs.front(), p, cvh.vs[1])) || is_positive(cross(cvh.vs.front(), cvh.vs.back(), p))) return RELA_PoP::outside_pop;
    auto it = std::lower_bound(cvh.vs.begin() + 1, cvh.vs.end(), p, [&](const Point &lhs, const Point &rhs) { return is_positive(cross(cvh.vs.front(), lhs, rhs)); }) - 1;
    auto next_it = cvh.next(it);
    auto res = sgn_cross(p, *it, *next_it);
    if (res) return ~res ? RELA_PoP::inside_pop : RELA_PoP::outside_pop;
    return !res && !is_positive(dot(p, *it, *next_it)) ? RELA_PoP::inside_pop : RELA_PoP::outside_pop;
}
}  // namespace tifa_libs::geo2d

#endif