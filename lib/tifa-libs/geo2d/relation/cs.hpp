#ifndef TIFALIBS_GEO2D_RELATION_CS_HPP
#define TIFALIBS_GEO2D_RELATION_CS_HPP

#include "tifa-libs/geo2d/util.hpp"
#include "tifa-libs/geo2d/circle_class.hpp"

#include "tifa-libs/geo2d/line.hpp"

namespace tifa_libs::geo2d {
// relation between circle and segment/line
enum RELA_CS {
    otherwise_cs,
    tagante_cs,
    intersect_cs,
};
constexpr RELA_CS relation_CS(const Circle &c, const Line &s) {
    data_t d = dist_PL(c.o, s);
    if (is_less(d, c.r)) return RELA_CS::intersect_cs;
    if (is_equal(d, c.r)) return RELA_CS::tagante_cs;
    return RELA_CS::otherwise_cs;
}
}  // namespace tifa_libs::geo2d

#endif