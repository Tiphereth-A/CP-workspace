#define DISABLE_PRAGMA_
#ifndef DISABLE_PRAGMA_
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#endif

#include <bits/stdc++.h>
#ifdef __GNUG__
#include <bits/stdtr1c++.h>
#include <ext/algorithm>
#include <ext/rb_tree>
#include <ext/rope>
#include <ext/vstring.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
#endif
#ifdef LOCAL_
#include <dbg.h>
#endif

template <class T>
concept iterable = requires(T v) {
    { v.begin() } -> std::same_as<typename T::iterator>;
    { v.end() } -> std::same_as<typename T::iterator>;
};
template <class T>
concept container = iterable<T> && !std::derived_from<T, std::basic_string<typename T::value_type>>;

template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using vvvec = vec<vvec<T>>;
template <class U, class T>
using vvp = vvec<std::pair<U, T>>;

template <class T>
using ptt = std::pair<T, T>;
template <class T>
using pt3 = std::tuple<T, T, T>;
template <class T>
using pt4 = std::tuple<T, T, T, T>;

template <class T>
using pq = std::priority_queue<T>;
template <class T>
using pqg = std::priority_queue<T, vec<T>, std::greater<T>>;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using isz = ptrdiff_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usz = size_t;

using f32 = float;
using f64 = double;
using f128 = long double;

using compi = std::complex<int>;
using compi64 = std::complex<i64>;
using compd = std::complex<double>;
using pii = ptt<int>;
using pii64 = ptt<i64>;


constexpr i8 operator""_i8(unsigned long long x) { return (i8)x; }
constexpr i16 operator""_i16(unsigned long long x) { return (i16)x; }
constexpr i32 operator""_i32(unsigned long long x) { return (i32)x; }
constexpr i64 operator""_i64(unsigned long long x) { return (i64)x; }
constexpr isz operator""_iz(unsigned long long x) { return (isz)x; }

constexpr u8 operator""_u8(unsigned long long x) { return (u8)x; }
constexpr u16 operator""_u16(unsigned long long x) { return (u16)x; }
constexpr u32 operator""_u32(unsigned long long x) { return (u32)x; }
constexpr u64 operator""_u64(unsigned long long x) { return (u64)x; }
constexpr usz operator""_uz(unsigned long long x) { return (usz)x; }


#define for_(i, l, r, ...) for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##end; ++i)
#define fors_(i, l, r, s, ...) for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##end; i += s)
#define rfor_(i, r, l, ...) for (std::make_signed_t<decltype(r - l)> i = (r), i##end = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##end; --i)
#define rfors_(i, r, l, s, ...) for (std::make_signed_t<decltype(r - l)> i = (r), i##end = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##end; i -= s)
#define fori_(it, l, r) for (auto it = (l); it != (r); ++it)
#define ins_(a) std::inserter((a), (a).begin())
#define all_(a) (a).begin(), (a).end()
#define rall_(a) (a).rbegin(), (a).rend()
#define range_(a, l, r) ((a).begin() + (l)), ((a).begin() + (r))
#define rrange_(a, l, r) ((a).rbegin() + (l)), ((a).rbegin() + (r))
#define run_(cmd, post_cmd) \
    {                       \
        cmd;                \
        post_cmd;           \
    }
#define runexit_(cmd) run_(cmd, exit(0))
#define runreturn_(cmd, ...) run_(cmd, return __VA_OPT__((__VA_ARGS__)))
#define runbreak_(cmd) run_(cmd, break)
#define runcontinue_(cmd) run_(cmd, continue)

template <container T>
std::istream &operator<<(std::istream &is, T &x) {
    for (auto &i : x) is >> x;
    return is;
}
template <container T>
std::ostream &operator<<(std::ostream &os, T const &x) {
#ifdef LOCAL_
    if (&os == &std::cerr && x.begin() == x.end()) return os << "[]";
#endif
    if (x.begin() == x.end()) return os;
#ifdef LOCAL_
    if (&os == &std::cerr) os << '[';
    if (&os == &std::cerr)
        for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", ";
    else
#endif
        for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
    os << x.back();
#ifdef LOCAL_
    if (&os == &std::cerr) os << ']';
#endif
    return os;
}

template <class T>
constexpr auto chkmin(T &a, T b) -> bool { return b < a ? a = b, true : false; }
template <class T>
constexpr auto chkmax(T &a, T b) -> bool { return a < b ? a = b, true : false; }

template <class... Ts>
void debug(Ts const &...args) {
#ifdef LOCAL_
    ((std::cerr << args << '\n'), ...);
#endif
}
#define debug_line_ (std::cerr << __LINE__ << ' ' << __FUNCTION__ << std::endl)
#define debug_withname_(var) debug(#var, var)
#ifndef LOCAL_
#define dbg(...) (__VA_ARGS__)
#endif

// constexpr i64 MOD = 998244353;
constexpr i64 MOD = 1e9 + 7;
constexpr f64 EPS = 1e-8;
constexpr char DIR_DRUL[4] = {'D', 'R', 'U', 'L'};
constexpr char DIR_SENW[4] = {'S', 'E', 'N', 'W'};
constexpr pii DIR4[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
constexpr pii DIR8[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
constexpr pii DIRH[8] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
const std::string RES_YN[2] = {"NO", "YES"};
const std::string RES_Yn[2] = {"No", "Yes"};
const std::string RES_yn[2] = {"no", "yes"};
const std::string RES_POSS[2] = {"IMPOSSIBLE", "POSSIBLE"};
const std::string RES_Poss[2] = {"Impossible", "Possible"};
const std::string RES_poss[2] = {"impossible", "possible"};
const std::string RES_Ab[2] = {"Bob", "Alice"};
// const i64 EXP10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
// const i64 FACT[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

template <u32 n>
constexpr i64 EXP10_impl_() { return EXP10_impl_<n - 1>() * 10; }
template <>
constexpr i64 EXP10_impl_<0>() { return 1; }
template <u32 n>
constexpr i64 EXP10 = EXP10_impl_<n>();

template <u32 n>
constexpr i64 FACT10_impl_() { return FACT10_impl_<n - 1>() * n; }
template <>
constexpr i64 FACT10_impl_<0>() { return 1; }
template <u32 n>
constexpr i64 FACT = FACT10_impl_<n>();


using namespace std;


const auto STATIC__ = []() {
    return 0;
}();

// #define MULTI_CASES
auto solve([[maybe_unused]] int t_ = 0) -> void {
}

int main() {
#ifdef LOCAL_
    auto CLOCK_ST_ = std::chrono::high_resolution_clock::now();
    std::cerr << std::boolalpha << std::fixed << std::setprecision(6);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int i_ = STATIC__;
    // std::cout << std::fixed << std::setprecision(12);

#ifdef MULTI_CASES
    int t_ = 0;
    std::cin >> t_;
    for (i_ = 0; i_ < t_; ++i_)
#endif
        debug("Case", i_), solve(i_);
#ifdef LOCAL_
    auto CLOCK_ED_ = std::chrono::high_resolution_clock::now();
    std::clog << "\n---\nTime used: " << std::chrono::duration_cast<std::chrono::nanoseconds>(CLOCK_ED_ - CLOCK_ST_).count() * 1e-6l << " ms" << std::endl;
#endif
    return 0;
}