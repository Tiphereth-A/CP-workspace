#ifndef TIFALIBS_GEO2D_CVH_CLASS_HPP
#define TIFALIBS_GEO2D_CVH_CLASS_HPP

#include <iostream>

#include "tifa-libs/geo2d/util.hpp"
#include "tifa-libs/geo2d/polygon_class.hpp"

#include "tifa-libs/geo2d/line.hpp"

namespace tifa_libs::geo2d {
struct ConvexHull: public Polygon {
    ConvexHull() = default;
    explicit ConvexHull(size_t size_): Polygon(size_) {}
    explicit ConvexHull(const cont_t<Point> &vs_, bool inited = false, bool strict = true): Polygon(vs_) {
        if (!inited) strict ? init() : init_nonstrict();
    }

    friend std::istream &operator>>(std::istream &is, ConvexHull &rhs) {
        for (auto &i : rhs.vs) is >> i;
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const ConvexHull &rhs) {
        if (rhs.vs.empty()) return os;
        for (auto it = rhs.vs.begin(); it != rhs.vs.end() - 1; ++it) os << *it << ' ';
        return os << rhs.vs.back();
    }


    ConvexHull &init() {
        ptrdiff_t sz = vs.size();
        if (sz <= 1) return *this;
        resort();
        cont_t<Point> cvh(sz * 2);
        ptrdiff_t sz_cvh = 0;
        for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
            while (sz_cvh > 1 && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0) --sz_cvh;
        for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
            while (sz_cvh > t && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0) --sz_cvh;
        cvh.resize(sz_cvh - 1);
        vs = cvh;
        return *this;
    }
    ConvexHull &init_nonstrict() {
        reunique();
        ptrdiff_t sz = vs.size();
        if (sz <= 1) return *this;
        cont_t<Point> cvh(sz * 2);
        ptrdiff_t sz_cvh = 0;
        for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
            while (sz_cvh > 1 && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) < 0) --sz_cvh;
        for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
            while (sz_cvh > t && sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) < 0) --sz_cvh;
        cvh.resize(sz_cvh - 1);
        vs = cvh;
        return *this;
    }

    data_t diameter() const {
        size_t sz = vs.size();
        if (sz <= 1) return data_t{};
        size_t is = 0, js = 0;
        for (size_t k = 1; k < sz; ++k) {
            is = vs[k] < vs[is] ? k : is;
            js = vs[js] < vs[k] ? k : js;
        }
        size_t i = is, j = js;
        data_t ret = dist_PP(vs[i], vs[j]);
        do {
            (++(((vs[next(i)] - vs[i]) ^ (vs[next(j)] - vs[j])) >= 0 ? j : i)) %= sz;
            ret = std::max(ret, dist_PP(vs[i], vs[j]));
        } while (i != is || j != js);
        return ret;
    }

    TIFALIBS_GEO2D_FNUC_iSELF1__(ConvexHull, minkowski_sum_nonstrict, const ConvexHull &, rhs, {
        size_t n = vs.size(), m = rhs.vs.size();
        if (!m) return *this;
        if (!n) return *this = rhs;
        cont_t<Point> result;
        result.reserve(n + m);
        size_t midxl = 0;
        for (size_t i = 1; i < n; ++i) midxl = vs[i] < vs[midxl] ? i : midxl;
        size_t midxr = 0;
        for (size_t i = 1; i < m; ++i) midxr = rhs[i] < rhs[midxr] ? i : midxr;
        bool fl = false, fr = false;
        for (size_t idxl = midxl, idxr = midxr; !(idxl == midxl && fl) || !(idxr == midxr && fr);) {
            Point diffl = vs[next(idxl)] - vs[idxl];
            Point diffr = rhs[rhs.next(idxr)] - rhs[idxr];
            bool f = !(idxl == midxl && fl) && ((idxr == midxr && fr) || is_positive(diffl ^ diffr));
            result.push_back(vs[idxl] + rhs[idxr] + (f ? diffl : diffr));
            (f ? idxl : idxr) = (f ? next(idxl) : rhs.next(idxr));
            (f ? fl : fr) |= !(f ? idxl : idxr);
        }
        vs = result;
        return *this;
    });
    TIFALIBS_GEO2D_FNUC_iSELF1__(ConvexHull, minkowski_sum, const ConvexHull &, rhs, { return do_minkowski_sum_nonstrict(rhs).init(); });
    TIFALIBS_GEO2D_FNUC_iSELF1__(ConvexHull, ins_CVHhP, const Line &, l, {
        size_t sz = vs.size();
        cont_t<Point> cvc;
        for (size_t i = 0; i < sz; ++i) {
            Point p1 = vs[i], p2 = vs[next(i)];
            ptrdiff_t d1 = sgn_cross(l.l, l.r, p1), d2 = sgn_cross(l.l, l.r, p2);
            if (d1 >= 0) cvc.push_back(p1);
            if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, l));
        }
        vs = cvc;
        return *this;
    })
};
}  // namespace tifa_libs::geo2d

#endif