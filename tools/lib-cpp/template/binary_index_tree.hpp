#pragma once

namespace my_template {
#include <algorithm>
#include <cstddef>

template <size_t N, typename Tp, bool _clear = false>
class BIT {
  protected:
    Tp tree[N];

    constexpr ptrdiff_t lowbit(ptrdiff_t x) const { return x & (-x); }

  public:
    BIT() {
        if (_clear) this->clear();
    }

    void clear() { memset(tree, 0, sizeof(tree)); }
    void modify(ptrdiff_t pos, Tp val = 1) {
        for (ptrdiff_t i = std::clamp(pos, ptrdiff_t(0), ptrdiff_t(N) - 1); i < N; i += lowbit(i)) tree[i] += val;
    }
    Tp query(ptrdiff_t pos) const {
        Tp ret = 0;
        for (ptrdiff_t i = std::clamp(pos, ptrdiff_t(0), ptrdiff_t(N) - 1); i; i = i - lowbit(i)) ret += tree[i];
        return ret;
    }
};

}  // namespace my_template
