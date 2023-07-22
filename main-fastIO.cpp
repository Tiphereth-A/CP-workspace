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


namespace fast_io {
namespace type_traits {
template <class Tp>
constexpr bool is_char_v = std::is_same_v<Tp, char> || std::is_same_v<Tp, signed char> || std::is_same_v<Tp, unsigned char>;
template <class Tp>
constexpr bool is_int_v = (std::is_integral_v<Tp> && std::is_signed_v<Tp> && !is_char_v<Tp>) || std::is_same_v<Tp, __int128_t>;
template <class Tp>
constexpr bool is_uint_v = (std::is_integral_v<Tp> && std::is_unsigned_v<Tp> && !is_char_v<Tp>) || std::is_same_v<Tp, __uint128_t>;
template <class Tp>
using make_uint_t = typename std::conditional_t<(std::is_same_v<Tp, __int128_t> || std::is_same_v<Tp, __uint128_t>), std::common_type<__uint128_t>, typename std::conditional_t<std::is_signed_v<Tp>, std::make_unsigned<Tp>, std::common_type<Tp>>>::type;
}  // namespace type_traits

//! Will enter a dead loop if EOF occured during reading
template <size_t BUFFER_SIZE>
class FastIn {
    using self = FastIn<BUFFER_SIZE>;

  protected:
    char buffer_[BUFFER_SIZE], *now_ = buffer_, *end_ = buffer_;
    FILE *file_;

  public:
    explicit FastIn(FILE *file = stdin): file_(file) {}

    char fetch() { return now_ == end_ && (end_ = (now_ = buffer_) + fread(buffer_, 1, BUFFER_SIZE, file_), now_ == end_) ? EOF : *(now_)++; }
    char visit() { return now_ == end_ && (end_ = (now_ = buffer_) + fread(buffer_, 1, BUFFER_SIZE, file_), now_ == end_) ? EOF : *(now_); }
    void set_file(FILE *file) {
        file_ = file;
        now_ = end_ = buffer_;
    }

    bool iseof() { return visit() == EOF; }

    template <class Tp, std::enable_if_t<type_traits::is_int_v<Tp>> * = nullptr>
    self &read(Tp &n) {
        bool is_neg = false;
        char ch = fetch();
        while (!isdigit(ch)) {
            is_neg |= ch == '-';
            ch = fetch();
        }
        n = 0;
        while (isdigit(ch)) {
            (n *= 10) += ch & 0x0f;
            ch = fetch();
        }
        if (is_neg) n = -n;
        return *this;
    }
    template <class Tp, std::enable_if_t<type_traits::is_uint_v<Tp>> * = nullptr>
    self &read(Tp &n) {
        char ch = fetch();
        while (!isdigit(ch)) ch = fetch();
        n = 0;
        while (isdigit(ch)) {
            (n *= 10) += ch & 0x0f;
            ch = fetch();
        }
        return *this;
    }
    //! ignore cntrl and space
    template <class Tp, std::enable_if_t<type_traits::is_char_v<Tp>> * = nullptr>
    self &read(Tp &n) {
        while (!isgraph(n = fetch()))
            ;
        return *this;
    }
    self &read(char *n) {
        char *n_ = n;
        while (!isgraph(*n_ = fetch()))
            ;
        while (isgraph(*(++n_) = fetch()))
            ;
        *n_ = '\0';
        return *this;
    }
    self &read(std::string &n) {
        n.clear();
        char n_;
        while (!isgraph(n_ = fetch()))
            ;
        n.push_back(n_);
        while (isgraph(n_ = fetch())) n.push_back(n_);
        return *this;
    }
    template <class Tp, class Up>
    self &read(std::pair<Tp, Up> &p) { return read(p.first).read(p.second); }
    template <typename... Ts>
    self &read(std::tuple<Ts...> &p) {
        std::apply([&](Ts &...targs) { ((read(targs)), ...); }, p);
        return *this;
    }

    self &getline(char *n) {
        char *n_ = n;
        while (!isprint(*n_ = fetch()))
            ;
        while (isprint(*(++n_) = fetch()))
            ;
        *n_ = '\0';
        return *this;
    }
    self &getline(std::string &n) {
        char n_;
        while (!isprint(n_ = fetch()))
            ;
        n.push_back(n_);
        while (isprint(n_ = fetch())) n.push_back(n_);
        return *this;
    }

    //! NOT ignore cntrl and space
    template <class Tp, std::enable_if_t<type_traits::is_char_v<Tp>> * = nullptr>
    self &strict_read(Tp &n) {
        n = fetch();
        return *this;
    }

    template <class Tp>
    self &operator>>(Tp &val) { return read(val); }
};

template <size_t BUFFER_SIZE, size_t INT_BUFFER_SIZE>
class FastOut {
    using self = FastOut<BUFFER_SIZE, INT_BUFFER_SIZE>;

  private:
    char int_buffer_[INT_BUFFER_SIZE], *now_ib_ = int_buffer_;

  protected:
    FILE *file_;
    char *now_, buffer_[BUFFER_SIZE];
    const char * const end_ = buffer_ + BUFFER_SIZE;

  public:
    explicit FastOut(FILE *file = stdout): file_(file), now_(buffer_) {}

    self &operator=(const self &rhs) {
        file_ = rhs.file_;
        now_ = buffer_ + (rhs.now_ - rhs.buffer_);
        memcpy(buffer_, rhs.buffer_, sizeof(*buffer_) * (rhs.now_ - rhs.buffer_));
        return *this;
    }
    FastOut(const self &rhs) { *this = rhs; }

    ~FastOut() { flush(); }

    void flush() {
        fwrite(buffer_, 1, now_ - buffer_, file_);
        now_ = buffer_;
    }
    void rebind(FILE *file) { file_ = file; }

    template <class Tp, std::enable_if_t<type_traits::is_char_v<Tp>> * = nullptr>
    self &write(const Tp &n) {
        if (now_ == end_) flush();
        *(now_++) = n;
        return *this;
    }
    self &write(const char *n) {
        size_t len = strlen(n), l_;
        const char *n_ = n;
        while (now_ + len >= end_) {
            l_ = end_ - now_;
            memcpy(now_, n_, l_);
            now_ += l_;
            n_ += l_;
            len -= l_;
            flush();
        }
        memcpy(now_, n_, len);
        now_ += len;
        return *this;
    }
    template <class Tp, std::enable_if_t<type_traits::is_int_v<Tp>> * = nullptr>
    self &write(Tp n) {
        if (n < 0) {
            write('-');
            n = -n;
        }
        return write(static_cast<typename type_traits::make_uint_t<Tp>>(n));
    }
    template <class Tp, std::enable_if_t<type_traits::is_uint_v<Tp>> * = nullptr>
    self &write(Tp n) {
        now_ib_ = int_buffer_ + INT_BUFFER_SIZE - 1;
        do { *(--(now_ib_)) = char(n % 10) | '0'; } while (n /= 10);
        return write(now_ib_);
    }
    self &write(const std::string &str) { return write(str.c_str()); }
    template <class Tp, class Up>
    self &write(const std::pair<Tp, Up> &p) { return write(p.first).space().write(p.second); }
    template <typename... Ts>
    self &write(const std::tuple<Ts...> &p) {
        std::apply(
            [&](Ts const &...targs) {
                std::size_t n{0};
                ((write(targs).space_if(++n != sizeof...(Ts))), ...);
            },
            p);
        return *this;
    }

    self &linebreak() { return write('\n'); }
    self &linebreak_if(bool flag) { return flag ? linebreak() : *this; }
    self &space() { return write(' '); }
    self &space_if(bool flag) { return flag ? space() : *this; }

    template <class Tp>
    self &operator<<(const Tp &val) { return write(val); }
};

const std::size_t BUFFER_SIZE = (1 << 21) + 5;
FastIn<BUFFER_SIZE> fastin;
FastOut<BUFFER_SIZE, 21> fastout;
}  // namespace fast_io
using fast_io::fastin;
using fast_io::fastout;


template <class Tp>
using pi = std::pair<Tp, Tp>;
template <class Tp>
using vc = std::vector<Tp>;
template <class Tp>
using vvc = std::vector<std::vector<Tp>>;
template <class Tp>
using pq = std::priority_queue<Tp>;
template <class Tp>
using pqg = std::priority_queue<Tp, std::vector<Tp>, std::greater<Tp>>;


template <typename T>
using remove_cvref_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template <class T>
using is_iterable = typename std::conditional<std::is_same<decltype(std::declval<remove_cvref_t<T>>().begin()), typename remove_cvref_t<T>::iterator>::value && std::is_same<decltype(std::declval<remove_cvref_t<T>>().end()), typename remove_cvref_t<T>::iterator>::value, std::true_type, std::false_type>::type;

template <class T>
using is_container = typename std::conditional<is_iterable<T>::value && !std::is_base_of<T, std::basic_string<typename T::value_type>>::value, std::true_type, std::false_type>::type;


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
    fastin >> name
#define read_container_(type, name, size) \
    type name(size);                      \
    foreach_ref_(i, name) fastin >> i
#define intlt2str_(s) STR_____(s)
#define STR_____(s) #s
#define REif_(expression) \
    if (expression) throw std::runtime_error("Line " intlt2str_(__LINE__) ": やだもやだ、無理も無理〜")

template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool { return b < a ? a = b, true : false; }
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool { return a < b ? a = b, true : false; }
template <class Tp>
constexpr auto ispow2(Tp i) -> bool { return i && (i & -i) == i; }


#define OO_PTEQ_(op)                                                                                                                                                \
    template <class Tp, class Up>                                                                                                                                   \
    constexpr auto operator op(std::pair<Tp, Up> lhs, const std::pair<Tp, Up> &rhs) { return std::pair<Tp, Up>{lhs.first op rhs.first, lhs.second op rhs.second}; } \
    template <class Tp, class Up>                                                                                                                                   \
    constexpr std::pair<Tp, Up> &operator op##=(std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) {                                                             \
        lhs.first op## = rhs.first;                                                                                                                                 \
        lhs.second op## = rhs.second;                                                                                                                               \
        return lhs;                                                                                                                                                 \
    }

OO_PTEQ_(+)
OO_PTEQ_(-)
OO_PTEQ_(*)
OO_PTEQ_(/)
OO_PTEQ_(%)
OO_PTEQ_(&)
OO_PTEQ_(|)
OO_PTEQ_(^)
OO_PTEQ_(<<)
OO_PTEQ_(>>)

#undef OO_PTEQ_


template <class Tp, class Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) { return is >> p.first >> p.second; }
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
#ifdef LOCAL_
    if (&os == &std::cerr)
        return os << '<' << p.first << ", " << p.second << '>';
    else
#endif
        return os << p.first << ' ' << p.second;
}

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


template <class Tp>
void debug(Tp x) {
#ifdef LOCAL_
    std::cerr << x << std::endl;
#endif
}
template <class Tp, class... Ts>
void debug(Tp x, Ts... args) {
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

const u32 OFFSET = 5;
const u32 N = 5e5 + OFFSET;
const u32 M = 2e5 + OFFSET;
const u32 K = 21;
// const i64 MOD = 998244353;
const i64 MOD = 1e9 + 7;
const double EPS = 1e-6;
const i32 INF = 0x3f3f3f3f;
const i64 INF64 = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
const char DIR_DRUL[4] = {'D', 'R', 'U', 'L'};
const char DIR_SENW[4] = {'S', 'E', 'N', 'W'};
const pii DIR4[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const pii DIR8[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
const pii DIRH[8] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
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
    int i_ = STATIC__;

#ifdef MULTI_CASES
    int t_ = 0;
    fastin >> t_;
    for (i_ = 0; i_ < t_; ++i_)
#endif
        debug("Case", i_), solve(i_);
#ifdef LOCAL_
    auto CLOCK_ED_ = std::chrono::high_resolution_clock::now();
    std::clog << "\n---\nTime used: " << std::chrono::duration_cast<std::chrono::nanoseconds>(CLOCK_ED_ - CLOCK_ST_).count() * 1e-6l << " ms" << std::endl;
#endif
    return 0;
}