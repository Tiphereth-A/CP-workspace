#ifndef TIFALIBS_GEO2D_RELATION_POC_HPP
#define TIFALIBS_GEO2D_RELATION_POC_HPP

#include "tifa-libs/geo2d/util.hpp"
#include "tifa-libs/geo2d/circle_class.hpp"
#include "tifa-libs/geo2d/polygon_class.hpp"

#include "tifa-libs/geo2d/relation/cs.hpp"
#include "tifa-libs/geo2d/relation/pop.hpp"

namespace tifa_libs::geo2d {

// relation between polygon/convex hull and circle
enum RELA_PoC {
    otherwise_poc,
    touchin_poc,
    covered_poc
};

RELA_PoC relation_PoC(const Polygon &poly, const Circle &c) {
    auto x = RELA_PoC::covered_poc;
    if (relation_PoP(poly, c.o) != RELA_PoP::inside_pop) return RELA_PoC::otherwise_poc;
    for (size_t i = 0; i < poly.vs.size(); ++i) {
        size_t state = relation_CS(c, {poly.vs[i], poly.vs[poly.next(i)]});
        if (state == RELA_CS::intersect_cs) return RELA_PoC::otherwise_poc;
        if (state == RELA_CS::tagante_cs) x = RELA_PoC::touchin_poc;
    }
    return x;
}
}  // namespace tifa_libs::geo2d

#endif