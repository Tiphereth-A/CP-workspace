#include <bits/extc++.h>
#ifdef LOCAL_
#include <dbg.h>
#else
#define dbg(...) 42
#endif
using namespace std;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
#define fors_(i, l, r, s, ...) for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
#define rfors_(i, r, l, s, ...) for (i64 i = (r), i##e = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##e; i -= s)
#define rfor_(i, r, l, ...) rfors_(i, r, l, 1 __VA_OPT__(, ) __VA_ARGS__)

// #define MCAS
void solve([[maybe_unused]] int t_ = 0) {
}

signed main() {
#ifdef LOCAL_
    auto CLOCK_ST_ = chrono::high_resolution_clock::now();
    cerr << fixed << setprecision(6);
#endif
    cin.tie(nullptr)->sync_with_stdio(false);
    int i_ = 0;
#ifdef MCAS
    int t_ = 0;
    for ((cin >> t_), i_ = 0; i_ < t_; ++i_)
#endif
        dbg(i_), solve(i_);
#ifdef LOCAL_
    auto CLOCK_ED_ = chrono::high_resolution_clock::now();
    clog << "\n---\n"
         << chrono::duration_cast<chrono::nanoseconds>(CLOCK_ED_ - CLOCK_ST_).count() * 1e-6l << " ms" << endl;
#endif
    return 0;
}