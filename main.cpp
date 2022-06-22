#define DISABLE_PRAGMA_
#ifndef DISABLE_PRAGMA_
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#endif

// #ifdef __GNUG__
// #include <bits/extc++.h>
// #else
#include <bits/stdc++.h>
// #endif

#ifdef DISABLE_ASSERT_
#undef assert
#define assert(...) 1
#endif

using namespace std;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;

#define OPERATOR_OVERRIED_PAIR_(oper)                                                                     \
    template <typename Tp, typename Up>                                                                   \
    constexpr std::pair<Tp, Up> &operator oper##=(std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) { \
        lhs.first oper## = rhs.first;                                                                     \
        lhs.second oper## = rhs.second;                                                                   \
        return lhs;                                                                                       \
    }                                                                                                     \
    template <typename Tp, typename Up>                                                                   \
    constexpr std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs, const std::pair<Tp, Up> &rhs) { return lhs oper## = rhs; }

OPERATOR_OVERRIED_PAIR_(+)
OPERATOR_OVERRIED_PAIR_(-)
OPERATOR_OVERRIED_PAIR_(*)
OPERATOR_OVERRIED_PAIR_(/)
OPERATOR_OVERRIED_PAIR_(%)

#undef OPERATOR_OVERRIED_PAIR_

template <typename Tp>
using pi = std::pair<Tp, Tp>;
template <typename Tp>
using vc = std::vector<Tp>;
template <typename Tp>
using vvc = std::vector<std::vector<Tp>>;
template <typename Tp>
using pq = std::priority_queue<Tp>;
template <typename Tp>
using pqg = std::priority_queue<Tp, std::vector<Tp>, std::greater<Tp>>;
template <typename Tp>
using hset = std::unordered_set<Tp>;
template <typename Key, typename Tp, typename Hash = std::hash<Key>>
using hmap = std::unordered_map<Key, Tp, Hash>;

using compi = std::complex<int>;
using compi64 = std::complex<i64>;
using compd = std::complex<double>;
using pii = pi<int>;
using pii64 = pi<i64>;
using vi = vc<int>;
using vi64 = vc<i64>;
using vvi = vvc<int>;
using vvi64 = vvc<i64>;
using vpi = vc<pii>;
using vpi64 = vc<pii64>;
using pqi = pq<int>;
using pqi64 = pq<i64>;
using pqgi = pqg<int>;
using pqgi64 = pqg<i64>;

#define for_(i, l, r, vars...) for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define rfor_(i, r, l, vars...) for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vars; i >= i##end; --i)
#define foreach_val_(i, container) for (auto i : (container))
#define foreach_ref_(i, container) for (auto &i : (container))
#define foreach_cref_(i, container) for (const auto &i : (container))
#define foreach_rref_(i, container) for (auto &&i : (container))
#define foreach_binding_(container, vars...) for (auto &&[vars] : container)
#define foreach_iter_(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define foreach_iter_range_(it, container, l, r) for (auto it = (container).begin() + (l); it != (container).begin() + (r); ++it)
#define foreach_riter_(it, container) for (auto it = (container).rbegin(); it != (container).rend(); ++it)
#define foreach_riter_range_(it, container, l, r) for (auto it = (container).rbegin() + (l); it != (container).rbegin() + (r); ++it)
#define ins_(a) std::inserter((a), (a).begin())
#define all_(a) (a).begin(), (a).end()
#define rall_(a) (a).rbegin(), (a).rend()
#define range_(a, l, r) ((a).begin() + (l)), ((a).begin() + (r))
#define rrange_(a, l, r) ((a).rbegin() + (l)), ((a).rbegin() + (r))
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
#define read_var_(type, name) \
    type name;                \
    std::cin >> name
#define read_container_(type, name, size) \
    type name(size);                      \
    foreach_ref_(i, name) std::cin >> i;

template <class Tp>
auto chkmin(Tp &a, Tp b) -> bool { return b < a ? a = b, true : false; };
template <class Tp>
auto chkmax(Tp &a, Tp b) -> bool { return a < b ? a = b, true : false; };
template <typename Tp>
auto discretization(Tp &var) -> Tp {
    Tp d__(var);
    std::sort(d__.begin(), d__.end());
    d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
    for (auto &i : var) i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
    return d__;
};
template <typename Tp>
auto ispow2(Tp i) -> bool { return i && (i & -i) == i; }

template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
    if (&os == &std::cerr) return os << "(" << p.first << ", " << p.second << ")";
    return os << p.first << " " << p.second;
}
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os, const Container &x) {
    if (&os == &std::cerr) os << "[";
    if (&os == &std::cerr)
        for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", ";
    else
        for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
    os << x.back();
    if (&os == &std::cerr) os << "]";
    return os;
}

template <typename Tp>
inline void debug(Tp x) {
#ifdef LOCAL_
    std::cerr << x << std::endl;
#endif
}
template <typename Tp, typename... Args>
inline void debug(Tp x, Args... args) {
#ifdef LOCAL_
    std::cerr << x << ' ';
    debug(args...);
#endif
}
#define debug_line_ (std::cerr << __LINE__ << ' ' << __FUNCTION__ << std::endl)
#define debug_withname_(var) debug(#var, var)

const u32 OFFSET = 5;
const u32 N = 1e5 + OFFSET;
const u32 M = 2e5 + OFFSET;
const u32 K = 21;
const u32 MOD = 1e9 + 7;
const double EPS = 1e-6;
const i32 INF = 0x3f3f3f3f;
const i64 INF64 = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
const pii DIR4[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
const pii DIR8[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const i32 EXP10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
const i32 FACT[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
const std::string RES_YN[2] = {"NO", "YES"};
const std::string RES_Yn[2] = {"No", "Yes"};
const std::string RES_yn[2] = {"no", "yes"};
const std::string RES_POSS[2] = {"IMPOSSIBLE", "POSSIBLE"};
const std::string RES_Poss[2] = {"Impossible", "Possible"};
const std::string RES_poss[2] = {"impossible", "possible"};

const auto STATIC__ = []() { return 0; }();

// #define MULTI_CASES
inline auto solve([[maybe_unused]] int t_) -> void {
}

int main() {
#ifdef LOCAL_
    auto CLOCK_ST_ = std::chrono::high_resolution_clock::now();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int i_ = STATIC__;

#ifdef MULTI_CASES
    int t_;
    std::cin >> t_;
    for (i_ = 1; i_ <= t_; ++i_)
#endif
        debug("Case", i_), solve(i_);
#ifdef LOCAL_
    auto CLOCK_ED_ = std::chrono::high_resolution_clock::now();
    std::clog << "\n---\n"
              << "Time used: " << std::chrono::duration_cast<std::chrono::nanoseconds>(CLOCK_ED_ - CLOCK_ST_).count() * 1e-6l << " ms" << std::endl;
#endif
    return 0;
}