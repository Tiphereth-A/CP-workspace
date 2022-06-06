#pragma once

namespace my_template {
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <functional>

template <size_t DATA_SZ, size_t BLOCK_SZ, typename data_t, typename init_func = std::function<data_t(size_t)>, typename query_func = std::function<data_t(const data_t &, const data_t &)>>
class Blocking {
  protected:
    init_func ifunc;
    query_func qfunc;
    data_t data[DATA_SZ], block[BLOCK_SZ];

    inline size_t get_block_index(size_t x) const { return x / BLOCK_SZ; }
    inline size_t get_block_begin(size_t x) const { return x * BLOCK_SZ; }
    inline size_t get_block_end(size_t x) const { return get_block_begin(x) + BLOCK_SZ; }

  public:
    Blocking() = delete;
    Blocking(init_func ifunc, query_func qfunc):
        ifunc(ifunc), qfunc(qfunc) {}

    void clear() {
        memset(data, 0, sizeof(data));
        memset(block, 0, sizeof(block));
    }

    void init(size_t n) {
        for (size_t i = 0; i <= n; ++i) data[i] = ifunc(i);
        for (size_t i = 0; i <= get_block_index(n); ++i) block[i] = data[get_block_begin(i)];
        for (size_t i = 0; i <= get_block_index(n); ++i)
            for (size_t j = 1; j < BLOCK_SZ; ++j) block[i] = qfunc(block[i], data[get_block_begin(i) + j]);
    }

    data_t query(size_t l, size_t r) const {
        size_t _l = get_block_index(l), _r = get_block_index(r);
        data_t result = data[l];
        for (size_t i = _l + 1; i < _r; ++i) result = qfunc(result, block[i]);
        for (size_t i = l, _le = get_block_end(_l); i < _le; ++i) result = qfunc(result, data[i]);
        for (size_t i = get_block_end(_r - 1); i <= r; ++i) result = qfunc(result, data[i]);

        return result;
    }
};
}  // namespace my_template
