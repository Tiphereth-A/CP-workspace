#pragma once

namespace my_template {
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <functional>

template <size_t N, typename data_t, typename init_func, typename query_func>
class RMQ_ST {
  protected:
    init_func ifunc;
    query_func qfunc;
    data_t f[(size_t)log2(N) + 1][N];

    size_t log_table[N];

  public:
    RMQ_ST() {}

    void clear() { memset(f, 0, sizeof(f)); }

    void init(size_t n) {
        for (size_t i = 1; i <= n; ++i) f[0][i] = ifunc(i);
        for (size_t i = 1; i <= std::log2(n); ++i)
            for (size_t j = 1; j + (1 << i) - 1 <= n; ++j)
                f[i][j] = qfunc(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
    }

    data_t query(size_t l, size_t r) const {
        size_t _ = std::log2(r - l + 1);
        return qfunc(f[_][l], f[_][r - (1 << _) + 1]);
    }
};

//!
struct ifunc {
    int operator()(const size_t x) const;
};
//!
struct qfunc {
    int operator()(const int l, const int r) const;
};

}  // namespace my_template