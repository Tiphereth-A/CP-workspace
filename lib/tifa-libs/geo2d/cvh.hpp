#ifndef TIFALIBS_GEO2D_CVH_HPP
#define TIFALIBS_GEO2D_CVH_HPP

#include <deque>

#include "tifa-libs/geo2d/util.hpp"
#include "tifa-libs/geo2d/cvh_class.hpp"
#include "tifa-libs/geo2d/triangle_class.hpp"

namespace tifa_libs::geo2d {
// Min distance between two convex hulls
data_t min_dis_CVH(const ConvexHull &cvhl, const ConvexHull &cvhr) {
    size_t is = 0, js = 0;
    size_t szl = cvhl.vs.size(), szr = cvhr.vs.size();
    data_t ans = DATA_MAX;
    for (size_t i = 0; i < szl; ++i) is = cvhl[i].y < cvhl[is].y ? i : is;
    for (size_t i = 0; i < szr; ++i) js = cvhr[i].y < cvhr[js].y ? i : js;
    for (size_t i = 0; i < szl; ++i) {
        ptrdiff_t state;
        while ((state = sgn((cvhl[is] - cvhl[cvhl.next(is)]) ^ (cvhr[js] - cvhr[cvhr.next(js)]))) < 0) js = cvhr.next(js);
        ans = std::min(ans, state ? dist_PS(cvhr[js], {cvhl[is], cvhl[cvhl.next(is)]}) : dist_SS({cvhl[is], cvhl[cvhl.next(is)]}, {cvhr[js], cvhr[cvhr.next(js)]}));
        is = cvhl.next(is);
    }
    return ans;
}

// Max distance between two convex hulls
data_t max_dis_CVH(const ConvexHull &cvhl, const ConvexHull &cvhr) {
    size_t is = 0, js = 0;
    size_t szl = cvhl.vs.size(), szr = cvhr.vs.size();
    data_t ans{};
    for (size_t i = 0; i < szl; ++i) is = cvhl[i].y < cvhl[is].y ? i : is;
    for (size_t i = 0; i < szr; ++i) js = cvhr[i].y < cvhr[js].y ? i : js;
    for (size_t i = 0; i < szl; ++i) {
        ptrdiff_t state;
        ans = std::max(ans, dist_PP(cvhl[is], cvhr[js]));
        while ((state = sgn((cvhl[is] - cvhl[cvhl.next(is)]) ^ (cvhr[js] - cvhr[cvhr.next(js)]))) < 0) ans = std::max(ans, dist_PP(cvhl[is], cvhr[js = cvhr.next(js)]));
        ans = std::max(ans, dist_PP(cvhr[js], cvhl[cvhl.next(is = cvhl.next(is))]));
        if (!state) {
            ans = std::max(ans, dist_PP(cvhl[is], cvhr[js]));
            js = cvhr.next(js);
        }
    }
    return ans;
}

// Coverage rectangle with min area
Polygon coverage_rect_with_min_area(const ConvexHull &lhs) {
    size_t sz = lhs.vs.size();
    if (sz == 0) return lhs;
    if (sz == 1) return Polygon{cont_t<Point>{lhs[0], lhs[0], lhs[0], lhs[0]}};
    if (sz == 2) return Polygon{cont_t<Point>{lhs[0], lhs[0], lhs[1], lhs[1]}};
    data_t ans = DATA_MAX;
    size_t r = 1, p = 1, q = 1;
    size_t ans_i, ans_r, ans_p, ans_q;
    for (size_t i = 0; i < sz; ++i) {
        while (!is_negative(cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(r)]) - cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[r]))) r = lhs.next(r);
        while (!is_negative(dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(p)]) - dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[p]))) p = lhs.next(p);
        if (i == 0) q = p;
        while (!is_positive(dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(q)]) - dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[q]))) q = lhs.next(q);
        data_t tmp = cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[r]) * (dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[p]) - dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[q])) / (lhs.vs[i] - lhs.vs[lhs.next(i)]).norm();
        if (ans > tmp) {
            ans = tmp;
            ans_i = i;
            ans_r = r;
            ans_p = p;
            ans_q = q;
        }
    }
    Point dir = Line{lhs[ans_i], lhs[lhs.next(ans_i)]}.direction(), vdir = rot90(dir);
    Line li{lhs[ans_i], lhs[ans_i] + dir}, lp{lhs[ans_p], lhs[ans_p] + vdir}, lr{lhs[ans_r], lhs[ans_r] + dir}, lq{lhs[ans_q], lhs[ans_q] + vdir};
    Polygon ret{cont_t<Point>{ins_LL(li, lp), ins_LL(lp, lr), ins_LL(lr, lq), ins_LL(lq, li)}};
    return ret;
}

// Coverage rectangle with min circum
Polygon coverage_rect_with_min_circum(const ConvexHull &lhs) {
    size_t sz = lhs.vs.size();
    if (sz == 0) return lhs;
    if (sz == 1) return Polygon{cont_t<Point>{lhs[0], lhs[0], lhs[0], lhs[0]}};
    if (sz == 2) return Polygon{cont_t<Point>{lhs[0], lhs[0], lhs[1], lhs[1]}};
    data_t ans = DATA_MAX;
    size_t r = 1, p = 1, q = 1;
    size_t ans_i = 0, ans_r, ans_p, ans_q;
    for (size_t i = 0; i < sz; ++i) {
        while (!is_negative(cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(r)]) - cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[r]))) r = lhs.next(r);
        while (!is_negative(dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(p)]) - dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[p]))) p = lhs.next(p);
        if (i == 0) q = p;
        while (!is_positive(dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(q)]) - dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[q]))) q = lhs.next(q);
        data_t tmp = (cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[r]) + (dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[p]) - dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[q]))) / (lhs.vs[i] - lhs.vs[lhs.next(i)]).abs();
        if (ans > tmp) {
            ans = tmp;
            ans_i = i;
            ans_r = r;
            ans_p = p;
            ans_q = q;
        }
    }
    Point dir = Line{lhs[ans_i], lhs[lhs.next(ans_i)]}.direction(), vdir = rot90(dir);
    Line li{lhs[ans_i], lhs[ans_i] + dir}, lp{lhs[ans_p], lhs[ans_p] + vdir}, lr{lhs[ans_r], lhs[ans_r] + dir}, lq{lhs[ans_q], lhs[ans_q] + vdir};
    Polygon ret{cont_t<Point>{ins_LL(li, lp), ins_LL(lp, lr), ins_LL(lr, lq), ins_LL(lq, li)}};
    return ret;
}

ConvexHull ins_hP(cont_t<Line> vl) {
    auto check = [](const Line &u, const Line &v, const Line &w) -> bool { return w.is_include_strict(ins_LL(u, v)); };
    std::sort(vl.begin(), vl.end());
    vl.erase(std::unique(vl.begin(), vl.end()), vl.end());
    if (vl.size() < 3) return ConvexHull{};
    std::deque<Line> q;
    for (auto it = vl.begin(); it != vl.end(); ++it) {
        if (it != vl.begin() && is_same_dir(*it, *(it - 1))) continue;
        while (q.size() > 1 && !check(*(q.rbegin() + 1), q.back(), *it)) q.pop_back();
        while (q.size() > 1 && !check(*(q.begin() + 1), q.front(), *it)) q.pop_front();
        q.push_back(*it);
    }
    while (q.size() > 2 && !check(*(q.rbegin() + 1), q.back(), q.front())) q.pop_back();
    while (q.size() > 2 && !check(*(q.begin() + 1), q.front(), q.back())) q.pop_front();
    cont_t<Point> ret;
    for (size_t i = 0; i < q.size(); ++i) ret.push_back(ins_LL(q[i], q[(i + 1) % q.size()]));
    return ConvexHull{ret, true};
}

// Triangle inside with max area
Triangle max_area_T(const ConvexHull &cvh) {
    if (cvh.vs.size() < 3) return Triangle{cvh.vs[0], cvh.vs[0], cvh.vs[0]};
    size_t j = 1, k = 2;
    data_t ans = 0, tmp, new_tmp;
    size_t is = 0, js = 1, ks = 2;
    for (size_t i = 0; i < cvh.vs.size(); ++i) {
        if (i == j) j = cvh.next(j);
        if (j == k) k = cvh.next(k);
        if (is_greater(tmp = cross(cvh.vs[i], cvh.vs[j], cvh.vs[k]), ans)) {
            ans = tmp;
            is = i;
            js = j;
            ks = k;
        }
        bool f = true;
        while (f) {
            f = false;
            if (is_greater(new_tmp = cross(cvh.vs[i], cvh.vs[j], cvh.vs[cvh.next(k)]), tmp)) {
                k = cvh.next(k);
                if (is_greater(tmp = new_tmp, ans)) {
                    ans = tmp;
                    is = i;
                    js = j;
                    ks = k;
                }
                f = true;
            }
            if (is_greater(new_tmp = cross(cvh.vs[i], cvh.vs[cvh.next(j)], cvh.vs[k]), tmp)) {
                j = cvh.next(j);
                if (is_greater(tmp = new_tmp, ans)) {
                    ans = tmp;
                    is = i;
                    js = j;
                    ks = k;
                }
                f = true;
            }
        }
    }
    return Triangle{cvh.vs[is], cvh.vs[js], cvh.vs[ks]};
}
}  // namespace tifa_libs::geo2d

#endif