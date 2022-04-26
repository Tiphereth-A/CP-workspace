#pragma once

#include "template\binary_index_tree.hpp"

namespace my_template {
#include <cstddef>
#include <cstdint>

namespace Cantor_expansion {
const uint64_t N = 1e6 + 5;
const uint64_t MOD = ULLONG_MAX;

uint64_t n, p[N];

BIT<N, int64_t, true> tr;

uint64_t frac[N] = {1};
void init(uint64_t n) {
    tr.clear();
    for (uint64_t i = 1; i <= n; ++i) frac[i] = i * frac[i - 1] % MOD;
}

uint64_t main(uint64_t n, const uint64_t a[]) {
    init(n);
    uint64_t ret = 1;
    for (uint64_t i = n; i; --i) {
        p[i] = tr.query(a[i]);
        tr.modify(a[i]);
    }
    for (uint64_t i = 1; i <= n; ++i) ret = (ret + p[i] * frac[n - i] % MOD) % MOD;
    return ret;
}
} // namespace Cantor_expansion

namespace reverse_Cantor_expansion {
const uint64_t N = 64;

uint64_t n, p[N];

// based on BIT, need discretization before using
template <uint64_t N>
class BT : public BIT<N, uint64_t, true> {
  protected:
    uint64_t LOG_N;

    uint64_t sum(uint64_t pos) const {
        uint64_t ret = 0;
        for (uint64_t i = pos; i; i = (int64_t)i - lowbit(i)) ret += tree[i];
        return ret;
    }
    uint64_t query_rk(uint64_t pos) const {
        uint64_t idx = 0;
        for (uint64_t i = LOG_N; ~i; --i) {
            idx += 1 << i;
            if (idx >= N || tree[idx] >= pos)
                idx -= 1 << i;
            else
                pos -= tree[idx];
        }
        return idx + 1;
    }

  public:
    BT() : BIT<N, uint64_t, true>() { LOG_N = ceil(log2(N)); }
    void insert(uint64_t pos) { modify(pos); }
    void remove(uint64_t pos) { modify(pos, -1); }
    uint64_t kth_num(uint64_t k) const { return query_rk(k); }
};
BT<N> tr;

uint64_t frac[N] = {1};
void init(uint64_t n) {
    tr.clear();
    for (uint64_t i = 1; i <= n; ++i) frac[i] = i * frac[i - 1];
}

void main(uint64_t num, uint64_t a[], uint64_t n) {
    init(n);
    --num;
    for (uint64_t i = 1; i <= n; ++i) tr.insert(i);
    for (uint64_t i = 1; i <= n; ++i) {
        p[i] = num / frac[n - i];
        num %= frac[n - i];
    }
    for (uint64_t i = 1; i <= n; ++i) tr.remove(a[i] = tr.kth_num(p[i] + 1));
}
} // namespace reverse_Cantor_expansion

} // namespace my_template