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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <magic/visualize.h>
#pragma GCC diagnostic pop
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

#define fors_(i, l, r, s, ...) for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
#define rfors_(i, r, l, s, ...) for (i64 i = (r), i##e = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##e; i -= s)
#define rfor_(i, r, l, ...) rfors_(i, r, l, 1 __VA_OPT__(, ) __VA_ARGS__)
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


template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) { return is >> p.first >> p.second; }
template <class T, class U>
std::ostream &operator<<(std::ostream &os, std::pair<T, U> const &p) { return os << p.first << ' ' << p.second; }
template <class... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
    std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p);
    return is;
}
template <class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> const &p) {
    std::apply(
        [&](Ts const &...targs) {
            usz n = 0;
            ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
        },
        p);
    return os;
}
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
template <std::floating_point T>
constexpr int sgn(T x, double EPS = 1e-8) { return (x > EPS) - (x < -EPS); }

#ifndef LOCAL_
#define dbg(...) 42
#define debug(...) 42
#define debugl_ 42
#define debugn_(...) 42
#else
template <class... Ts>
void debug(Ts const &...args) { ((std::cerr << args << ' '), ...), std::cerr << std::endl; }
#define debugl_ debug(__LINE__, __PRETTY_FUNCTION__)
#define debugn_(name) debug(#name, name)
#endif

// constexpr i64 MOD = 998244353;
constexpr i64 MOD = 1'000'000'007;
constexpr char DIR_DRUL[4] = {'D', 'R', 'U', 'L'};
constexpr char DIR_SENW[4] = {'S', 'E', 'N', 'W'};
constexpr pii DIR4[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
constexpr pii DIR8[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
const std::string RES_YN[2] = {"NO", "YES"};
const std::string RES_Yn[2] = {"No", "Yes"};
const std::string RES_yn[2] = {"no", "yes"};
const std::string RES_POSS[2] = {"IMPOSSIBLE", "POSSIBLE"};
const std::string RES_Poss[2] = {"Impossible", "Possible"};
const std::string RES_poss[2] = {"impossible", "possible"};
const std::string RES_Ab[2] = {"Bob", "Alice"};


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
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int i_ = STATIC__;
    // std::cout << std::fixed << std::setprecision(12);

#ifdef MULTI_CASES
    int t_ = 0;
    std::cin >> t_;
    for (i_ = 0; i_ < t_; ++i_)
#endif
        dbg(i_), solve(i_);
#ifdef LOCAL_
    auto CLOCK_ED_ = std::chrono::high_resolution_clock::now();
    std::clog << "\n---\nTime used: " << std::chrono::duration_cast<std::chrono::nanoseconds>(CLOCK_ED_ - CLOCK_ST_).count() * 1e-6l << " ms" << std::endl;
#endif
    return 0;
}