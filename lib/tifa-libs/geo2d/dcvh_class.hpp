#ifndef TIFALIBS_GEO2D_DCVH_CLASS_HPP
#define TIFALIBS_GEO2D_DCVH_CLASS_HPP


#include "tifa-libs/geo2d/util.hpp"
#include "tifa-libs/geo2d/cvh_class.hpp"

namespace tifa_libs::geo2d {
// Dynamic Convex Hull
class DCVH {
  protected:
    // Dynamic half Convex Hull
    struct DHCVH {
        ptrdiff_t sgn_ = 1;
        cont_set_t<Point> vs;

        DHCVH() = default;
        explicit DHCVH(ptrdiff_t sgn_): sgn_(sgn_) {}

        bool contains(const Point &p) const {
            auto it = vs.lower_bound({p.x, -DATA_MAX});
            if (it == vs.end()) return false;
            if (it->x == p.x) return sgn(p.y - it->y) * sgn_ <= 0;
            if (it == vs.begin()) return false;
            auto j = it;
            return sgn_cross(*(--j), *it, p) * sgn_ <= 0;
        }
        bool erase(cont_set_t<Point>::const_iterator it) {
            if (it == vs.begin()) return false;
            auto j = it, k = it;
            if (++k == vs.end()) return false;
            return sgn_cross(*(--j), *it, *k) * sgn_ >= 0 ? vs.erase(it), true : false;
        }
        DHCVH &insert(const Point &p) {
            if (contains(p)) return *this;
            auto tmp = vs.lower_bound({p.x, -DATA_MAX});
            if (tmp != vs.end() && tmp->x == p.x) vs.erase(tmp);
            vs.insert(p);
            auto i = vs.find(p), j = i;
            if (i != vs.begin()) {
                --j;
                while (erase(j++)) --j;
            }
            if (++j != vs.end())
                while (erase(j--)) ++j;
            return *this;
        }
    } hcvh_up{1}, hcvh_down{-1};

  public:
    DCVH() = default;


    bool contains(const Point &p) const { return hcvh_up.contains(p) && hcvh_down.contains(p); }
    DCVH &insert(const Point &p) {
        hcvh_up.insert(p);
        hcvh_down.insert(p);
        return *this;
    }
    ConvexHull to_CVH() const {
        ConvexHull ret;
        for (auto it = hcvh_up.vs.begin(); it != hcvh_up.vs.end(); ++it) ret.vs.push_back(*it);
        for (auto it = hcvh_down.vs.begin(); it != hcvh_down.vs.end(); ++it) ret.vs.push_back(*it);
        ret.resort_in_counterclockwise();
        return ret;
    }
};

}  // namespace tifa_libs::geo2d

#endif