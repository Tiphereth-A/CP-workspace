#ifndef DISABLE_PRAGMA_
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif
#ifdef __GNUG__
#include <bits/extc++.h>
#else
#include <bits/stdc++.h>
#endif
using namespace std;
using i64 = std::int64_t;
using u64 = std::uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using vi = std::vector<int>;
using vi64 = std::vector<i64>;
using pii = std::pair<int, int>;
using pii64 = std::pair<i64, i64>;

#define for_(i, l, r, vars...) for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define rfor_(i, r, l, vars...) for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vars; i >= i##end; --i)
#define foreach_val_(i, container) for (auto i : container)
#define foreach_ref_(i, container) for (auto &i : container)
#define foreach_cref_(i, container) for (const auto &i : container)
#define foreach_rref_(i, container) for (auto &&i : container)
#define foreach_binding_(container, vars...) for (auto &&[##vars] : container)
#define foreach_iter_(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define foreach_iter_range_(it, container, l, r) for (auto it = (container).begin() + l; it != (container).begin() + r; ++it)
#define foreach_riter_(it, container) for (auto it = (container).rbegin(); it != (container).rend(); ++it)
#define foreach_riter_range_(it, container, l, r) for (auto it = (container).rbegin() + l; it != (container).rbegin() + r; ++it)
#define ins_(a) std::inserter((a), (a).begin())
#define all_(a) (a).begin(), (a).end()
#define set_nul_(a) memset(a, 0, sizeof(a))
#define set_inf_(a) memset(a, 0x3f, sizeof(a))
#define set_nul_n_(a, n) memset(a, 0, sizeof(*(a)) * (n))
#define set_inf_n_(a, n) memset(a, 0x3f, sizeof(*(a)) * (n))
#define run_exec_(expressions, after_process) \
    {                                         \
        expressions;                          \
        after_process;                        \
    }
#define run_exit_(expressions) run_exec_(expressions, exit(0))
#define run_return_(expressions, val) run_exec_(expressions, return val)
#define run_return_void_(expressions) run_exec_(expressions, return )
#define run_break_(expressions) run_exec_(expressions, break)
#define run_continue_(expressions) run_exec_(expressions, continue)
#define mid_(l, r) ((l) + (((r) - (l)) >> 1))
#define len_(l, r) ((r) - (l) + 1)
#define lowbit_(x) (1 << __builtin_ctz(x))
#define lowbit_64_(x) (1 << __builtin_ctzll(x))
#define debug_line_ (std::cerr << __LINE__ << ' ' << __FUNCTION__ << std::endl)
inline void debug() { std::cerr << std::endl; }
template <typename Tp, typename... Args>
inline void debug(Tp x, Args... args) {
    std::cerr << x << ' ';
    debug(args...);
}
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }

const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET;
const uint32_t M = 2e5 + OFFSET;
const uint32_t K = 21;
const uint32_t MOD = 1e9 + 7;
const double EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INF64 = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
const pii DIR4[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
const pii DIR8[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const int EXP10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
const int FACT[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

const auto STATIC__ = []() { return 0.0; }();

#define MULTI_CASES
inline auto solve() -> void {
}

int main() {
#ifdef LOCAL_
    auto CLOCK_ST_ = std::chrono::high_resolution_clock::now();
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef MULTI_CASES
    int _t;
    cin >> _t;
    while (_t--)
#endif
        solve();

#ifdef LOCAL_
    std::clog << "\n---\n"
              << "Time used: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - CLOCK_ST_).count() * 1e-6 << " ms" << std::endl;
#endif
    return 0;
}