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


template <typename T>
using remove_cvref_t = typename std::remove_cv_t<typename std::remove_reference_t<T>>;

template <class T>
using is_iterable = typename std::conditional_t<std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().begin()), typename remove_cvref_t<T>::iterator> && std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().end()), typename remove_cvref_t<T>::iterator>, std::true_type, std::false_type>;

template <class T>
using is_container = typename std::conditional_t<is_iterable<T>::value && !std::is_base_of_v<T, std::basic_string<typename T::value_type>>, std::true_type, std::false_type>;


template <class T>
using pi = std::pair<T, T>;
template <class T>
using vc = std::vector<T>;
template <class T>
using vvc = std::vector<std::vector<T>>;
template <class T>
using pq = std::priority_queue<T>;
template <class T>
using pqg = std::priority_queue<T, std::vector<T>, std::greater<T>>;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;

using compi = std::complex<int>;
using compi64 = std::complex<i64>;
using compd = std::complex<double>;
using pii = pi<int>;
using pii64 = pi<i64>;


#define for_(i, l, r, vars...) for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define for_step_(i, l, r, s, vars...) for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; i <= i##end; i += s)
#define rfor_(i, r, l, vars...) for (std::make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vars; i >= i##end; --i)
#define rfor_step_(i, r, l, s, vars...) for (std::make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vars; i >= i##end; i -= s)
#define foreach_val_(i, container) for (auto i : container)
#define foreach_ref_(i, container) for (auto &i : container)
#define foreach_cref_(i, container) for (const auto &i : container)
#define foreach_rref_(i, container) for (auto &&i : container)
#define foreach_binding_(container, vars...) for (auto &&[vars] : container)
#define foreach_iter_(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define foreach_iter_range_(it, container, l, r) for (auto it = (container).begin() + l; it != (container).begin() + r; ++it)
#define foreach_riter_(it, container) for (auto it = (container).rbegin(); it != (container).rend(); ++it)
#define foreach_riter_range_(it, container, l, r) for (auto it = (container).rbegin() + l; it != (container).rbegin() + r; ++it)
#define ins_(a) std::inserter((a), (a).begin())
#define all_(a) (a).begin(), (a).end()
#define rall_(a) (a).rbegin(), (a).rend()
#define range_(a, l, r) ((a).begin() + (l)), ((a).begin() + (r))
#define rrange_(a, l, r) ((a).rbegin() + (l)), ((a).rbegin() + (r))
#define set_nul_(a) memset(a, 0, sizeof(a))
#define set_inf_(a) memset(a, 0x3f, sizeof(a))
#define set_nul_n_(a, n) memset(a, 0, sizeof(*(a)) * (n))
#define set_inf_n_(a, n) memset(a, 0x3f, sizeof(*(a)) * (n))
#define run_exec_(expressions, post_process) \
    {                                        \
        expressions;                         \
        post_process;                        \
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
    foreach_ref_(i, name) std::cin >> i
#define intlt2str_(s) STR_____(s)
#define STR_____(s) #s
#define REif_(expression) \
    if (expression) throw std::runtime_error("Line " intlt2str_(__LINE__) ": やだもやだ、無理も無理〜")

template <class T>
constexpr auto chkmin(T &a, T b) -> bool { return b < a ? a = b, true : false; }
template <class T>
constexpr auto chkmax(T &a, T b) -> bool { return a < b ? a = b, true : false; }
template <class T>
constexpr auto ispow2(T i) -> bool { return i && (i & -i) == i; }


template <class T, std::enable_if_t<is_container<T>::value> * = nullptr>
std::ostream &operator<<(std::ostream &os, const T &x) {
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
#ifndef LOCAL_
#define dbg(...) (__VA_ARGS__)
#endif

// constexpr i64 MOD = 998244353;
constexpr i64 MOD = 1e9 + 7;
constexpr double EPS = 1e-6;
constexpr i32 INF = 0x3f3f3f3f;
constexpr i64 INF64 = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.);
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
// const int64_t EXP10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
// const int64_t FACT[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

template <size_t N_>
constexpr int64_t EXP10_impl_() { return EXP10_impl_<N_ - 1>() * 10; }
template <>
constexpr int64_t EXP10_impl_<0>() { return 1; }
template <size_t N_>
constexpr int64_t EXP10 = EXP10_impl_<N_>();

template <size_t N_>
constexpr int64_t FACT10_impl_() { return FACT10_impl_<N_ - 1>() * N_; }
template <>
constexpr int64_t FACT10_impl_<0>() { return 1; }
template <size_t N_>
constexpr int64_t FACT = FACT10_impl_<N_>();


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