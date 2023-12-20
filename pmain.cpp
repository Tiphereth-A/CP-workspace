// #pragma comment(linker, "/STACK:102400000,102400000")
// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
template <class Tp>
using vec = vector<Tp>;
template <class Tp>
using vvec = vector<vector<Tp>>;

#define for_(i, l, r, ...) for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; ++i)
#define fors_(i, l, r, s, ...) for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define rfor_(i, r, l, ...) for (i64 i = (r), i##e = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##e; --i)
#define rfors_(i, r, l, s, ...) for (i64 i = (r), i##e = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##e; i -= s)

template <class... Ts>
void debug(Ts const &...args) {
#ifdef LOCAL_
    ((cerr << args << ' '), ...);
    cerr << '\n';
#endif
}
#define dbgl_ (cerr << __LINE__ << ' ' << __PRETTY_FUNCTION__ << endl)
#define dbgn_(var) debug(#var, var)

// #define MCAS
void solve([[maybe_unused]] int t_ = 0) {
    for_(i, 1, 10) cout << "114514\n";
}

signed main() {
#ifdef LOCAL_
    auto CLOCK_ST_ = chrono::high_resolution_clock::now();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cerr << fixed << setprecision(6);
    int i_ = 0;
#ifdef MCAS
    int t_ = 0;
    cin >> t_;
    for (i_ = 0; i_ < t_; ++i_)
#endif
        debug("Case", i_), solve(i_);
#ifdef LOCAL_
    auto CLOCK_ED_ = chrono::high_resolution_clock::now();
    clog << "\n---\n"
         << chrono::duration_cast<chrono::nanoseconds>(CLOCK_ED_ - CLOCK_ST_).count() * 1e-6l << " ms" << endl;
#endif
    return 0;
}