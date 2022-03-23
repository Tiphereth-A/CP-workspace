#ifndef TIFALIBS_GEO2D_CIRCLE_HPP
#define TIFALIBS_GEO2D_CIRCLE_HPP

#include "tifa-libs/geo2d/util.hpp"
#include "tifa-libs/geo2d/triangle_class.hpp"
#include "tifa-libs/geo2d/circle_class.hpp"

#include "tifa-libs/geo2d/relation/cc.hpp"
#include "tifa-libs/geo2d/relation/cp.hpp"

namespace tifa_libs::geo2d {
// intersection point of circle and line
// maybe 0, 2 (maybe duplicate)
cont_t<Point> ins_CL(const Circle &c, const Line &l1) {
    if (is_greater(std::abs((c.o - l1.l) ^ (l1.r - l1.l) / dist_PP(l1.l, l1.r)), c.r)) return {};
    data_t x = (l1.l - c.o) * (l1.r - l1.l), y = l1.direction().norm(), d = std::max(x * x - y * ((l1.l - c.o).norm() - c.r * c.r), data_t{});
    Point m = l1.l - l1.direction() * (x / y), dr = l1.direction() * (sqrt(d) / y);
    return {m - dr, m + dr};
}
// intersection point of two circles
//! need to check whether two circles are the same
// maybe 0, 2 (maybe duplicate)
cont_t<Point> ins_CC(const Circle &c1, const Circle &c2) {
    assert(!is_equal(c1.o.x, c2.o.x) || !is_equal(c1.o.y, c2.o.y) || !is_equal(c1.r, c2.r));
    auto state = relation_CC(c1, c2);
    if (state == RELA_CC::lyingin_cc || state == RELA_CC::lyingout_cc) return {};
    data_t d = std::min(dist_PP(c1.o, c2.o), c1.r + c2.r);
    data_t y = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d), x = sqrt(c1.r * c1.r - y * y);
    Point dr = (c2.o - c1.o).do_unit();
    Point q1 = c1.o + dr * y, q2 = dr.do_rot90() * x;
    return {q1 - q2, q1 + q2};
}
// make circle by 3 point passed through
constexpr Circle make_C_PPP(const Point &p1, const Point &p2, const Point &p3) {
    Point o = Triangle{p1, p2, p3}.center_O();
    return {o, dist_PP(o, p1)};
}
// make circle by radius and 2 point passed through
// maybe 0, 2 (maybe duplicate)
cont_t<Circle> make_C_rPP(data_t r, const Point &p1, const Point &p2) {
    cont_t<Point> ps = ins_CC({p1, r}, {p2, r});
    cont_t<Circle> ret;
    for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
    return ret;
}
// make circle by radius, a point passed through and a tagante lines
// maybe 0, 2 (maybe duplicate)
cont_t<Circle> make_C_rPL(data_t r, const Point &p, const Line &l) {
    data_t dis = dist_PL(p, l);
    if (is_positive(dis - r * 2)) return {};
    Point dir = l.direction();
    dir *= r / dir.abs();
    Point dirl = rot90(dir), dirr = rot270(dir);
    if (is_zero(dis)) return {{p + dirl, r}, {p + dirr, r}};
    Circle c{p, r};
    cont_t<Point> ps = ins_CL(c, {l.l + dirl, l.r + dirl});
    if (ps.size() == 0) ps = ins_CL(c, {l.l + dirr, l.r + dirr});
    cont_t<Circle> ret;
    for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
    return ret;
}
// make circle by radius and 2 tagante lines
// maybe 0, 4
cont_t<Circle> make_C_rLL(data_t r, const Line &l1, const Line &l2) {
    if (is_parallel(l1, l2)) return {};
    Point dir1 = l1.direction(), dir2 = l2.direction();
    dir1 *= r / dir1.abs();
    dir2 *= r / dir2.abs();
    Point dirl1 = rot90(dir1), dirr1 = rot270(dir1), dirl2 = rot90(dir2), dirr2 = rot270(dir2);
    Line u1 = Line{l1.l + dirl1, l1.r + dirl1};
    Line u2 = Line{l1.l + dirr1, l1.r + dirr1};
    Line v1 = Line{l2.l + dirl2, l2.r + dirl2};
    Line v2 = Line{l2.l + dirr2, l2.r + dirr2};
    return {{ins_LL(u1, v1), r}, {ins_LL(u1, v2), r}, {ins_LL(u2, v1), r}, {ins_LL(u2, v2), r}};
}
// make circle by radius and 2 external tagante circle
// maybe 0, 2 (maybe duplicate)
cont_t<Circle> make_C_rCC_ex(data_t r, const Circle &c1, const Circle &c2) {
    if (relation_CC(c1, c2) == RELA_CC::lyingin_cc) return {};
    cont_t<Point> ps = ins_CC({c1.o, c1.r + r}, {c2.o, c2.r + r});
    cont_t<Circle> ret;
    for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
    return ret;
}

// geometry inverse of a point
constexpr Point inv_P2P(const Circle &c, const Point &p) {
    Point v = p - c.o;
    return c.o + v * (c.r * c.r / v.norm());
}
// geometry inverse of a circle which DOES NOT pass through the inversion center
constexpr Circle inv_C2C(const Circle &c, const Circle &c2) {
    Point v = (c2.o - c.o).do_unit();
    Point p1 = inv_P2P(c, c2.o + v * c2.r), p2 = inv_P2P(c, c2.o - v * c2.r);
    return {mid_point(p1, p2), dist_PP(p1, p2) / 2};
}
// geometry inverse of a circle which pass through the inversion center
constexpr Line inv_C2L(const Circle &c, const Circle &c2) {
    Point v = (c2.o - c.o).do_rot90();
    return {inv_P2P(c, c2.o + v), inv_P2P(c, c2.o - v)};
}
// geometry inverse of a line
constexpr Circle inv_L2C(const Circle &c, const Line &l) {
    Point p1 = inv_P2P(c, l.l), p2 = inv_P2P(c, l.r);
    return make_C_PPP(p1, p2, c.o);
}

// tagante points of point to circle // maybe 0, 2 (maybe duplicate)
cont_t<Point> tan_CP(const Circle &c, const Point &p) {
    Point v = p - c.o;
    data_t x = v.norm(), d = x - c.r * c.r;
    if (is_negative(d)) return {};
    Point q1 = c.o + v * (c.r * c.r / x);
    Point q2 = v.do_rot90() * (c.r * sqrt(d) / x);
    // counter clock-wise
    return {q1 - q2, q1 + q2};
}
// external tagante lines of 2 circles // maybe 0, 2 (maybe duplicate)
cont_t<Line> extan_CC(const Circle &c1, const Circle &c2) {
    if (is_equal(c1.o.x, c2.o.x) && is_equal(c1.o.y, c2.o.y)) return {};
    cont_t<Line> ret;
    if (is_equal(c1.r, c2.r)) {
        Point dr = (c2.o - c1.o).do_unit().do_rot90() * c1.r;
        ret.emplace_back(c1.o + dr, c2.o + dr);
        ret.emplace_back(c1.o - dr, c2.o - dr);
    } else {
        Point p = (c2.o * c1.r - c1.o * c2.r) / (c1.r - c2.r);
        cont_t<Point> ps = tan_CP(c1, p), qs = tan_CP(c2, p);
        // c1 counter-clock wise
        for (size_t i = 0; i < std::min(ps.size(), qs.size()); ++i) ret.emplace_back(ps[i], qs[i]);
    }
    return ret;
}
// internal tagante lines of 2 disjoint circles // maybe 0, 2 (maybe duplicate)
cont_t<Line> intan_CC(const Circle &c1, const Circle &c2) {
    if (is_equal(c1.o.x, c2.o.x) && is_equal(c1.o.y, c2.o.y)) return {};
    cont_t<Line> ret;
    Point p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
    cont_t<Point> ps = tan_CP(c1, p), qs = tan_CP(c2, p);
    // c1 counter-clock wise
    for (size_t i = 0; i < std::min(ps.size(), qs.size()); ++i) ret.emplace_back(ps[i], qs[i]);
    return ret;
}

// area of intersection of circle and triangle
//! WITH DIRECTION, sgn is cross(c.o, p1, p2)
//! the center ot circle is also a endpoint of triangle
data_t sarea_CT(const Circle &c, const Point &p1, const Point &p2) {
    if (is_zero(cross(c.o, p1, p2))) return data_t{};
    cont_t<Point> is = ins_CL(c, {p1, p2});
    if (is.empty()) return c.area(ang_PP(p1 - c.o, p2 - c.o));
    bool b1 = is_greater(dist_PP(p1, c.o), c.r), b2 = is_greater(dist_PP(p2, c.o), c.r);
    if (b1 && b2) {
        data_t res = c.area(ang_PP(p1 - c.o, p2 - c.o));
        if (!is_positive(dot(is[0], p1, p2))) res -= c.crown_area(ang_PP(is[0] - c.o, is[1] - c.o));
        return res;
    }
    if (b1) return c.area(ang_PP(p1 - c.o, is[0] - c.o)) + cross(c.o, is[0], p2) / 2;
    if (b2) return c.area(ang_PP(is[1] - c.o, p2 - c.o)) + cross(c.o, p1, is[1]) / 2;
    return cross(c.o, p1, p2) / 2;
}
constexpr data_t area_CC(const Circle &lhs, const Circle &rhs) {
    auto relation = relation_CC(lhs, rhs);
    if (relation == RELA_CC::lyingout_cc || relation == RELA_CC::touchex_cc) return data_t{};
    if (relation == RELA_CC::lyingin_cc || relation == RELA_CC::touchin_cc) return std::min(
        lhs.area(), rhs.area());
    data_t d = dist_PP(lhs.o, rhs.o);
    return lhs.crown_area(std::acos((lhs.r * lhs.r + d * d - rhs.r * rhs.r) / (2 * lhs.r * d)) * 2) + rhs.crown_area(std::acos((rhs.r * rhs.r + d * d - lhs.r * lhs.r) / (2 * rhs.r * d)) * 2);
}

// min coverage circle of a set of points
//! accuracy maybe reduced without shuffling `vp` first
Circle min_cover_C(const cont_t<Point> &vp) {
    Circle ret{vp.front(), 0};
    size_t sz = vp.size();
    for (size_t i = 1; i < sz; ++i) {
        if (relation_CP(ret, vp[i]) != RELA_CP::outside_cp) continue;
        ret = Circle{vp[i], 0};
        for (size_t j = 0; j < i; ++j) {
            if (relation_CP(ret, vp[j]) != RELA_CP::outside_cp) continue;
            ret = Circle{mid_point(vp[i], vp[j]), dist_PP(vp[i], vp[j]) / 2};
            for (size_t k = 0; k < j; ++k) {
                if (relation_CP(ret, vp[k]) != RELA_CP::outside_cp) continue;
                ret = make_C_PPP(vp[i], vp[j], vp[k]);
            }
        }
    }
    return ret;
}
}  // namespace tifa_libs::geo2d

#endif