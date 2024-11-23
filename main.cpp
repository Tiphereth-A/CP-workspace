#include <bits/extc++.h>
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

#define int_type(w)                                                          \
    using i##w = int##w##_t;                                                 \
    using u##w = uint##w##_t;                                                \
    constexpr auto operator""_i##w(unsigned long long x) { return (i##w)x; } \
    constexpr auto operator""_u##w(unsigned long long x) { return (u##w)x; }
int_type(8);
int_type(16);
int_type(32);
int_type(64);
#undef int_type

using i128 = __int128_t;
using u128 = __uint128_t;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T, class C = std::less<T>>
using pq = __gnu_pbds::priority_queue<T, C>;
template <class T>
using pqg = pq<T, std::greater<T>>;
template <class T, bool enable_order = false, class C = std::less<T>>
using pbds_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, C, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template <class K, class V, class C = std::less<K>>
using pbds_map = __gnu_pbds::tree<K, V, C, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define fors_(i, l, r, s, ...) for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
#define rfors_(i, r, l, s, ...) for (i64 i = (r), i##e = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##e; i -= s)
#define rfor_(i, r, l, ...) rfors_(i, r, l, 1 __VA_OPT__(, ) __VA_ARGS__)
#define fori_(it, l, r) for (auto it = (l); it != (r); ++it)
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
    return std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p), is;
}
template <class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> const &p) {
    return std::apply([&, n = 0](Ts const &...targs) mutable { ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...); }, p), os;
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
    if (&os == &std::cerr) {
        os << '[';
        for (auto nxt = x.begin(), it = nxt++; nxt != x.end(); ++it, ++nxt) os << *it << ", ";
    } else
#endif
        for (auto nxt = x.begin(), it = nxt++; nxt != x.end(); ++it, ++nxt) os << *it << ' ';
    os << *x.rbegin();
#ifdef LOCAL_
    if (&os == &std::cerr) os << ']';
#endif
    return os;
}

#ifndef LOCAL_
#define dbg(...) 42
#define debug(...) 42
#else
template <class... Ts>
void debug(Ts const &...args) { ((std::cerr << args << ' '), ...), std::cerr << std::endl; }
#endif

constexpr char DIR_DRUL[4] = {'D', 'R', 'U', 'L'};
constexpr char DIR_SENW[4] = {'S', 'E', 'N', 'W'};
constexpr std::pair<int, int> DIR4[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
constexpr std::pair<int, int> DIR8[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
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