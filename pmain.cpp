// #pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
using ull = unsigned long long;
using u64 = ull;
using i128 = __int128_t;
using u128 = __uint128_t;
using ldb = long double;

using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

template <class T>
using vc = std::vector<T>;
template <class T>
using vvc = std::vector<std::vector<T>>;
template <class T>
using pq = std::priority_queue<T>;
template <class T>
using pqg = std::priority_queue<T, std::vector<T>, std::greater<T>>;


#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define fors_(i, l, r, s, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; i += s)
#define rfor_(i, r, l, v...) for (ll i = (r), i##e = (l), ##v; i >= i##e; --i)
#define rfors_(i, r, l, s, v...) for (ll i = (r), i##e = (l), ##v; i >= i##e; i -= s)
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