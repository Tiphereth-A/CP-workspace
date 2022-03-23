#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
ostream &operator<<(ostream &os, i128 n) {
    if (n < 0) {
        os << '-';
        n = -n;
    }
    if (n > 9) os << n / 10;
    os << (uint_fast8_t)(n % 10);
    return os;
}
ostream &operator<<(ostream &os, u128 n) {
    if (n > 9) os << n / 10;
    os << (uint_fast8_t)(n % 10);
    return os;
}

#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...) for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; i >= i##end; --i)
#define _foreach_val(i, container) for (auto i : container)
#define _foreach_ref(i, container) for (auto &i : container)
#define _foreach_cref(i, container) for (const auto &i : container)
#define _foreach_rref(i, container) for (auto &&i : container)
#define _foreach_iter(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define _foreach_iter_range(it, container, l, r) for (auto it = (container).begin() + l; it != (container).begin() + r; ++it)

#define _UID1(type, x, number) uniform_int_distribution<type> u_##x##1(1, number)
#define _UID0(type, x, number) uniform_int_distribution<type> u_##x##0(0, number)
#define _UID_n1(type, x, number) uniform_int_distribution<type> u_##x##n1(-1, number)
#define _UID_ratio(type, x, number, ratio) uniform_int_distribution<type> u_##x##ratio((type)(number * 0.##ratio), number)
#define _UID_nratio(type, x, number, ratio) uniform_int_distribution<type> u_##x##n##ratio(1, (type)(number * (1 - 0.##ratio)))

#define _UID(type, x, number, ratio) \
    const type x = number;           \
    _UID1(type, x, x);               \
    _UID0(type, x, x);               \
    _UID_n1(type, x, x);             \
    _UID_ratio(type, x, x, ratio);   \
    _UID_nratio(type, x, x, ratio)

using seed_type = uint64_t;

namespace generetor {
const uint64_t MOD = 998244353;
uniform_int_distribution<int64_t> u_mod(0, MOD - 1);

const int64_t KASE = 4e5;
uniform_int_distribution<int64_t> u_kase(1, KASE);

uniform_int_distribution<char> u_lower('a', 'z');
uniform_int_distribution<char> u_upper('A', 'Z');
uniform_int_distribution<int> u_bool(0, 1);
uniform_real_distribution<double> u_property(0, 1);

uniform_int_distribution<int32_t> u_non_neg_32(0, INT32_MAX);
uniform_int_distribution<int64_t> u_non_neg_64(0, INT64_MAX);

uniform_int_distribution<int32_t> u_pos_32(1, INT32_MAX);
uniform_int_distribution<int64_t> u_pos_64(1, INT64_MAX);

_UID(int32_t, M, 1e5, 95);
_UID(int32_t, N, 100, 95);

void main(const seed_type seed, [[maybe_unused]] const seed_type type) {
    mt19937_64 e(seed);
    int64_t n = u_N95(e);
    cout << n << endl;
    for (int64_t i = 0; i < n; ++i) cout << u_N0(e) << endl;
}
}  // namespace generetor


int main(int argc, char **argv) {
#ifndef _CLI_
    srand(time(nullptr));
    const seed_type seed = rand(), type = 0;
#else
    if (argc != 3) {
        cout << "Usage: gen seed type" << endl;
        return 1;
    }

    auto _get_seed = [](const char * const str) -> seed_type {
        auto ch = str;
        seed_type res = 0;
        while (*ch) {
            if (!isdigit(*ch)) continue;
            (res *= 10) += *(ch++) & 0x0f;
        }
        return res;
    };

    const seed_type seed = _get_seed(argv[1]), type = _get_seed(argv[2]);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    try {
        generetor::main(seed, type);
    } catch (exception &e) {
        cerr << e.what() << endl;
        return 2;
    }

    return 0;
}