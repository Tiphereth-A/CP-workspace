#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;
using u128 = __uint128_t;
ostream &operator<<(ostream &os, i128 n) {
    if (n < 0) {
        os << '-';
        n = -n;
    }
    if (n > 9) os << (i128)(n / 10);
    os << (uint_fast8_t)(n % 10);
    return os;
}
ostream &operator<<(ostream &os, u128 n) {
    if (n > 9) os << (u128)(n / 10);
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
#define _UID_ratio(type, x, number, ratio) uniform_int_distribution<type> u_##x##ratio(number * 0.##ratio, number)
#define _UID_nratio(type, x, number, ratio) uniform_int_distribution<type> u_##x##n##ratio(1, number *(1 - 0.##ratio))

#define _UID(type, x, number, ratio) \
    const type x = number;           \
    _UID1(type, x, x);               \
    _UID0(type, x, x);               \
    _UID_n1(type, x, x);             \
    _UID_ratio(type, x, x, ratio);   \
    _UID_nratio(type, x, x, ratio)

using seed_type = uint32_t;

namespace generetor {
const uint64_t MOD = 998244353;
uniform_int_distribution<int64_t> u_mod(0, MOD - 1);

const int64_t KASE = 4e5;
uniform_int_distribution<int64_t> u_kase(1, KASE);

uniform_int_distribution<char> u_lower('a', 'z');
uniform_int_distribution<char> u_upper('A', 'Z');
uniform_int_distribution<bool> u_bool(0, 1);
uniform_real_distribution<double> u_property(0, 1);

uniform_int_distribution<int32_t> u_non_neg_32(0, INT32_MAX);
uniform_int_distribution<int64_t> u_non_neg_64(0, INT64_MAX);

uniform_int_distribution<int32_t> u_pos_32(1, INT32_MAX);
uniform_int_distribution<int64_t> u_pos_64(1, INT64_MAX);

_UID(int32_t, M, 1e5, 95);
_UID(int32_t, N, 10, 95);

const uint64_t PRIME_1e18 = int64_t(1e18) - 11;
const uint64_t PRIME_1e9 = 1e9 + 7;

namespace primes {
const int N = 1e5 + 5, P = N;
bool vis[N];
int prime[P], cnt_prime;
inline void init_prime(const int &n = N - 1) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++cnt_prime] = i;
        for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
}  // namespace primes

const auto __STATIC__ = []() {
    primes::init_prime();
    memset(primes::vis, 0, sizeof(primes::vis));
    return 0;
}();


inline void main_des(const seed_type seed, [[maybe_unused]] const seed_type type) {
    default_random_engine e(seed);

    uniform_int_distribution<size_t> u_p(1, primes::cnt_prime);

    int32_t n = u_N95(e);
    cout << n << endl;

    int64_t x = 1e18;
    stack<size_t> idx;
    _for(i, 1, n) {
        int64_t now_m = 1;
        while (now_m <= M) {
            auto _ = u_p(e);
            while (primes::vis[_]) _ = u_p(e);
            if (now_m * primes::prime[_] > M) break;
            now_m *= primes::prime[_];
            idx.push(_);
        }
        while (!idx.empty()) {
            primes::vis[idx.top()] = true;
            idx.pop();
        }
        int64_t _ = max((int64_t)(u_property(e) / 100 * now_m) % x, (int64_t)(1));
        cout << now_m << ' ' << _ << endl;
        x /= _;
    }
}

inline void main(const seed_type seed, [[maybe_unused]] const seed_type type) {
    default_random_engine e(seed);
    int32_t n = u_N1(e);
    if (n < 3 && u_property(e) < 0.5) n = max(u_N1(e), (int32_t)(3));
    cout << n << endl;

    const int64_t x = min(1e5, pow(1e18, 1.0 / n));

    uniform_int_distribution<size_t> u_p(1, lower_bound(primes::prime + 1, primes::prime + primes::cnt_prime + 1, x) - primes::prime - 1);

    stack<size_t> idx;
    _for(i, 1, n) {
        int64_t now_m = 1;
        while (now_m <= x) {
            auto _ = u_p(e);
            while (primes::vis[_]) _ = u_p(e);
            if (now_m * primes::prime[_] > x) break;
            now_m *= primes::prime[_];
            idx.push(_);
        }
        while (!idx.empty()) {
            primes::vis[idx.top()] = true;
            idx.pop();
        }
        cout << now_m << ' ' << max((int64_t)(u_property(e) * now_m), (int64_t)(1)) << endl;
    }
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