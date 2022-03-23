#ifndef TIFALIBS_GEO2D_POLYGON_HPP
#define TIFALIBS_GEO2D_POLYGON_HPP

#include <iostream>

#include "tifa-libs/geo2d/util.hpp"
#include "tifa-libs/geo2d/polygon_class.hpp"

#include "tifa-libs/geo2d/circle.hpp"

namespace tifa_libs::geo2d {
data_t area_PoC(const Polygon &poly, const Circle &c) {
    data_t ans{};
    size_t sz = poly.vs.size();
    if (sz < 3) return ans;
    for (size_t i = 0; i < sz; ++i) ans += sarea_CT(c, poly[i], poly[poly.next(i)]);
    return std::abs(ans);
}
}  // namespace tifa_libs::geo2d

#endif