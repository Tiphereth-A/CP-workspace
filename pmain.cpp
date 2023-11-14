// #pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>

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

template <class T>
using ptt = std::pair<T, T>;
template <class T>
using pt3 = std::tuple<T, T, T>;
template <class T>
using pt4 = std::tuple<T, T, T, T>;

template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using vvvec = vec<vvec<T>>;
template <class U, class T>
using vvp = vvec<std::pair<U, T>>;

template <class T>
using pq = std::priority_queue<T>;
template <class T>
using pqg = std::priority_queue<T, vec<T>, std::greater<T>>;

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

#define for_(i, l, r, v...) for (i64 i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define fors_(i, l, r, s, v...) for (i64 i = (l), i##e = (r), ##v; i <= i##e; i += s)
#define rfor_(i, r, l, v...) for (i64 i = (r), i##e = (l), ##v; i >= i##e; --i)
#define rfors_(i, r, l, s, v...) for (i64 i = (r), i##e = (l), ##v; i >= i##e; i -= s)
#define forit_(it, cont) for (auto it = (cont).begin(); it != (cont).end(); ++it)
#define foritr_(it, cont, l, r) for (auto it = (cont).begin() + l; it != (cont).begin() + r; ++it)
#define rforit_(it, cont) for (auto it = (cont).rbegin(); it != (cont).rend(); ++it)
#define rforitr_(it, cont, l, r) for (auto it = (cont).rbegin() + l; it != (cont).rbegin() + r; ++it)
#define Rep for_
#define rep rfor_
template <typename... Ts>
void dec(Ts &...x) { ((--x), ...); }
template <typename... Ts>
void inc(Ts &...x) { ((++x), ...); }


template <class T>
void debug(T x) {
#ifdef LOCAL_
    std::cerr << x << std::endl;
#endif
}
template <class T, class... Ts>
void debug(T x, Ts... args) {
#ifdef LOCAL_
    std::cerr << x << ' ';
    debug(args...);
#endif
}
#define debug_line_ (std::cerr << __LINE__ << ' ' << __FUNCTION__ << std::endl)
#define debug_withname_(var) debug(#var, var)

using namespace std;


#define USE_CIN
// #define MULTI_CASES
void solve(int t_ = 0) {
}

signed main() {
#ifdef LOCAL_
    auto CLOCK_ST_ = std::chrono::high_resolution_clock::now();
#endif
#ifdef USE_CIN
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cerr << std::fixed << std::setprecision(6);
#endif
    int i_ = 0;
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