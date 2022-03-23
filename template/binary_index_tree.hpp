#pragma once

namespace my_template {
#include <cstddef>

template <size_t _N, typename Tp, bool _clear = false>
class BIT {
  protected:
    Tp tree[_N];

    constexpr size_t lowbit(ptrdiff_t x) const { return x & (-x); }

  public:
    BIT() {
        if (_clear) this->clear();
    }

    void clear() { memset(tree, 0, sizeof(tree)); }
    void modify(size_t pos, Tp val = 1) {
        for (size_t i = pos; i < _N; i += lowbit(i)) tree[i] += val;
    }
    Tp query(size_t pos) const {
        Tp ret = 0;
        for (size_t i = pos; i; i = (ptrdiff_t)i - lowbit(i)) ret += tree[i];
        return ret;
    }
};

} // namespace my_template
