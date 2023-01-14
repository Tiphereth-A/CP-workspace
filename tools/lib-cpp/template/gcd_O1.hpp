#pragma once

#include <initializer_list>
using std::initializer_list;

namespace my_template {
#include <algorithm>
#include <cstdint>

namespace Qgcd {
using data_type = uint32_t;
using idx_type = uint32_t;
const idx_type OFFSET = 5;
const idx_type N = 1e6 + OFFSET, SQRT_N = 1e3;

struct Factor3 {
    data_type a, b, c;

    Factor3(const data_type& _a = 0, const data_type& _b = 0, const data_type& _c = 0) : a(_a), b(_b), c(_c) {}
};

bool vis[N + OFFSET];
data_type prime[N / 10 + OFFSET];
idx_type cnt_prime;
Factor3 factors[N + OFFSET];
data_type _gcd[SQRT_N + OFFSET][SQRT_N + OFFSET];

void init() {
    factors[1] = {1, 1, 1};
    for (idx_type i = 2; i <= N; ++i) {
        if (!vis[i]) factors[i] = {1, 1, prime[++cnt_prime] = i};
        for (idx_type j = 1, ipj, apj; j <= cnt_prime && i * prime[j] <= N; ++j) {
            vis[ipj = i * prime[j]] = 1;
            apj = factors[i].a * prime[j];
            factors[ipj] = {apj, factors[i].b, factors[i].c};
            if (factors[ipj].a > factors[ipj].b) {
                std::swap(factors[ipj].a, factors[ipj].b);
                if (factors[ipj].b > factors[ipj].c) std::swap(factors[ipj].b, factors[ipj].c);
            }
            if (i % prime[j] == 0) break;
        }
    }
    for (idx_type i = 1; i <= SQRT_N; ++i) {
        _gcd[i][0] = _gcd[0][i] = _gcd[i][i] = i;
        for (idx_type j = 1; j < i; ++j) _gcd[i][j] = _gcd[j][i] = _gcd[j][i % j];
    }
}

const auto STATIC__ = []() {
    init();
    return 0;
}();

data_type main(data_type x, data_type y) {
    if (x <= SQRT_N && y <= SQRT_N) return _gcd[x][y];
    data_type ans = 1, _;
    for (data_type i : {factors[x].a, factors[x].b, factors[x].c}) {
        _ = i <= SQRT_N ? _gcd[i][y % i] : (y % i == 0) * (i - 1) + 1;
        y /= _;
        ans *= _;
    }
    return ans;
}
} // namespace Qgcd
} // namespace my_template