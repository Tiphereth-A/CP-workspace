#pragma once

namespace my_template {
#include <cstddef>

template <size_t N, class graph_t>
class Floyd {
  private:
    size_t n;
    graph_t spath[N][N];

  public:
    Floyd(size_t _n = N - 1) : n(_n) {
        memset(spath, 0x3f, sizeof(spath));
        for (size_t i = 1; i <= n; ++i) spath[i][i] = 0;
    }
    void resize(size_t _n) { n = _n; }
    void clear() { memset(spath, 0, sizeof(spath)); }
    void addedge(size_t from, size_t to, graph_t w = 1) { spath[from][to] = w; }
    void get_all_shortest_path() {
        for (size_t k = 1; k <= n; ++k)
            for (size_t i = 1; i <= n; ++i)
                for (size_t j = 1; j <= n; ++j)
                    if (spath[i][k] + spath[k][j] < spath[i][j]) spath[i][j] = spath[i][k] + spath[k][j];
    }
    const graph_t& operator()(size_t from, size_t to) { return spath[from][to]; }
};
} // namespace my_template