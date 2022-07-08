// #define DISABLE_PRAGMA_
#ifndef DISABLE_PRAGMA_
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#endif

#ifdef __GNUG__
#include <bits/extc++.h>
#else
#include <bits/stdc++.h>
#endif

namespace fast_io {
namespace type_traits {
template <class Tp>
using is_int = class std::conditional<(std::is_integral<Tp>::value && std::is_signed<Tp>::value) || std::is_same<Tp, __int128_t>::value, std::true_type, std::false_type>::type;

template <class Tp>
using is_uint = class std::conditional<(std::is_integral<Tp>::value && std::is_unsigned<Tp>::value) || std::is_same<Tp, __uint128_t>::value, std::true_type, std::false_type>::type;

template <class Tp>
using make_uint = class std::conditional<std::is_same<Tp, __int128_t>::value, __uint128_t, class std::conditional<std::is_signed<Tp>::value, std::make_unsigned<Tp>, std::common_type<Tp>>::type>::type;
}  // namespace type_traits

template <size_t BUFFER_SIZE>
class FastIn {
    using self = FastIn<BUFFER_SIZE>;

  protected:
    char buffer_[BUFFER_SIZE], *now_ = buffer_, *end_ = buffer_;
    FILE *file_;

  public:
    explicit FastIn(FILE *file = stdin) noexcept:
        file_(file) {}

    inline char fetch() noexcept { return this->now_ == this->end_ && (this->end_ = (this->now_ = this->buffer_) + fread(this->buffer_, 1, BUFFER_SIZE, this->file_), this->now_ == this->end_) ? EOF : *(this->now_)++; }
    inline char visit() noexcept { return this->now_ == this->end_ && (this->end_ = (this->now_ = this->buffer_) + fread(this->buffer_, 1, BUFFER_SIZE, this->file_), this->now_ == this->end_) ? EOF : *(this->now_); }
    inline void set_file(FILE *file) noexcept {
        this->file_ = file;
        now_ = end_ = buffer_;
    }

    template <class Tp, class std::enable_if<type_traits::is_int<Tp>::value>::type * = nullptr>
    inline self &read(Tp &n) noexcept {
        bool is_neg = false;
        char ch = this->fetch();
        while (!isdigit(ch)) {
            is_neg |= ch == '-';
            ch = this->fetch();
        }
        n = 0;
        while (isdigit(ch)) {
            (n *= 10) += ch & 0x0f;
            ch = this->fetch();
        }
        if (is_neg) n = -n;
        return *this;
    }
    template <class Tp, class std::enable_if<type_traits::is_uint<Tp>::value>::type * = nullptr>
    inline self &read(Tp &n) noexcept {
        char ch = this->fetch();
        while (!isdigit(ch)) ch = this->fetch();
        n = 0;
        while (isdigit(ch)) {
            (n *= 10) += ch & 0x0f;
            ch = this->fetch();
        }
        return *this;
    }
    inline self &read(char &n) noexcept {
        n = this->fetch();
        return *this;
    }
    inline self &read(char *n) noexcept {
        char *n_ = n;
        while (!isgraph(*n_ = this->fetch()))
            ;
        while (isgraph(*(++n_) = this->fetch()))
            ;
        *n_ = '\0';
        return *this;
    }
    inline self &read(std::string &n) noexcept {
        n.clear();
        char n_;
        while (!isgraph(n_ = this->fetch()))
            ;
        n.push_back(n_);
        while (isgraph(n_ = this->fetch())) n.push_back(n_);
        return *this;
    }
    inline self &getline(char *n) noexcept {
        char *n_ = n;
        while (!isprint(*n_ = this->fetch()))
            ;
        while (isprint(*(++n_) = this->fetch()))
            ;
        *n_ = '\0';
        return *this;
    }
    inline self &getline(std::string &n) noexcept {
        char n_;
        while (!isprint(n_ = this->fetch()))
            ;
        n.push_back(n_);
        while (isprint(n_ = this->fetch())) n.push_back(n_);
        return *this;
    }
    template <class Tp, class Up>
    inline self &read(std::pair<Tp, Up> &p) { return this->read(p.first).read(p.second); }
    template <class Tp, class Up, class Vp>
    inline self &read(std::tuple<Tp, Up, Vp> &p) { return this->read(std::get<0>(p)).read(std::get<1>(p)).read(std::get<2>(p)); }
    template <class Tp, class Up, class Vp, class Wp>
    inline self &read(std::tuple<Tp, Up, Vp, Wp> &p) { return this->read(std::get<0>(p)).read(std::get<1>(p)).read(std::get<2>(p)).read(std::get<3>(p)); }
};

template <size_t BUFFER_SIZE, size_t INT_BUFFER_SIZE>
class FastOut {
    using self = FastOut<BUFFER_SIZE, INT_BUFFER_SIZE>;

  private:
    char int_buffer_[INT_BUFFER_SIZE], *now_ib_;

  protected:
    char buffer_[BUFFER_SIZE], *now_ = buffer_;
    const char * const end_ = buffer_ + BUFFER_SIZE;
    FILE *file_;

  public:
    explicit FastOut(FILE *file = stdout) noexcept:
        file_(file) {}
    ~FastOut() noexcept { this->flush(); }

    inline void flush() noexcept {
        fwrite(this->buffer_, 1, this->now_ - this->buffer_, this->file_);
        this->now_ = this->buffer_;
    }
    inline void set_file(FILE *file) noexcept {
        this->file_ = file;
    }

    inline self &linebreak() noexcept {
        this->write('\n');
        return *this;
    }
    inline self &space() noexcept {
        this->write(' ');
        return *this;
    }

    inline self &write(const char &n) noexcept {
        if (this->now_ == this->end_) this->flush();
        *(this->now_++) = n;
        return *this;
    }
    inline self &write(const char *n) noexcept {
        size_t len = strlen(n), l_;
        const char *n_ = n;
        while (this->now_ + len >= this->end_) {
            l_ = this->end_ - this->now_;
            memcpy(this->now_, n_, l_);
            this->now_ += l_;
            n_ += l_;
            len -= l_;
            this->flush();
        }
        memcpy(this->now_, n_, len);
        this->now_ += len;
        return *this;
    }
    template <class Tp, class std::enable_if<type_traits::is_int<Tp>::value>::type * = nullptr>
    inline self &write(Tp n) noexcept {
        if (n < 0) {
            this->write('-');
            n = -n;
        }
        return this->write(static_cast<class type_traits::make_uint<Tp>::type>(n));
    }
    template <class Tp, class std::enable_if<type_traits::is_uint<Tp>::value>::type * = nullptr>
    inline self &write(Tp n) noexcept {
        this->now_ib_ = this->int_buffer_ + INT_BUFFER_SIZE - 1;
        do { *(--(this->now_ib_)) = char(n % 10) | '0'; } while (n /= 10);
        this->write(this->now_ib_);
        return *this;
    }
    inline self &write(const std::string &str) noexcept {
        this->write(str.c_str());
        return *this;
    }
    template <class Tp, class Up>
    inline self &write(const std::pair<Tp, Up> &p) { return this->write(p.first).space().write(p.second); }
    template <class Tp, class Up, class Vp>
    inline self &write(const std::tuple<Tp, Up, Vp> &p) { return this->write(std::get<0>(p)).space().write(std::get<1>(p)).space().write(std::get<2>(p)); }
    template <class Tp, class Up, class Vp, class Wp>
    inline self &write(const std::tuple<Tp, Up, Vp, Wp> &p) { return this->write(std::get<0>(p)).space().write(std::get<1>(p)).space().write(std::get<2>(p)).space().write(std::get<3>(p)); }
};

const std::size_t BUFFER_SIZE = 1 << 21;
FastIn<BUFFER_SIZE> fast_in;
FastOut<BUFFER_SIZE, 21> fast_out;
}  // namespace fast_io
using fast_io::fast_in;
using fast_io::fast_out;

using namespace std;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;
// using i128 = __int128_t;
// using u128 = __uint128_t;

#define OPERATOR_OVERRIED_PAIR_(oper)                                                                                                          \
    template <class Tp, class Up>                                                                                                              \
    constexpr std::pair<Tp, Up> &operator oper##=(std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) {                                      \
        lhs.first oper## = rhs.first;                                                                                                          \
        lhs.second oper## = rhs.second;                                                                                                        \
        return lhs;                                                                                                                            \
    }                                                                                                                                          \
    template <class Tp, class Up>                                                                                                              \
    constexpr std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs, const std::pair<Tp, Up> &rhs) { return lhs oper## = rhs; }                \
    template <class Tp, class Up, class Vp>                                                                                                    \
    constexpr std::tuple<Tp, Up, Vp> &operator oper##=(std::tuple<Tp, Up, Vp> &lhs, const std::tuple<Tp, Up, Vp> &rhs) {                       \
        std::get<0>(lhs) oper## = std::get<0>(rhs);                                                                                            \
        std::get<1>(lhs) oper## = std::get<1>(rhs);                                                                                            \
        std::get<2>(lhs) oper## = std::get<2>(rhs);                                                                                            \
        return lhs;                                                                                                                            \
    }                                                                                                                                          \
    template <class Tp, class Up, class Vp>                                                                                                    \
    constexpr std::tuple<Tp, Up, Vp> operator oper(std::tuple<Tp, Up, Vp> lhs, const std::tuple<Tp, Up, Vp> &rhs) { return lhs oper## = rhs; } \
    template <class Tp, class Up, class Vp, class Wp>                                                                                          \
    constexpr std::tuple<Tp, Up, Vp, Wp> &operator oper##=(std::tuple<Tp, Up, Vp, Wp> &lhs, const std::tuple<Tp, Up, Vp, Wp> &rhs) {           \
        std::get<0>(lhs) oper## = std::get<0>(rhs);                                                                                            \
        std::get<1>(lhs) oper## = std::get<1>(rhs);                                                                                            \
        std::get<2>(lhs) oper## = std::get<2>(rhs);                                                                                            \
        std::get<3>(lhs) oper## = std::get<3>(rhs);                                                                                            \
        return lhs;                                                                                                                            \
    }                                                                                                                                          \
    template <class Tp, class Up, class Vp, class Wp>                                                                                          \
    constexpr std::tuple<Tp, Up, Vp, Wp> operator oper(std::tuple<Tp, Up, Vp, Wp> lhs, const std::tuple<Tp, Up, Vp, Wp> &rhs) { return lhs oper## = rhs; }


OPERATOR_OVERRIED_PAIR_(+)
OPERATOR_OVERRIED_PAIR_(-)
OPERATOR_OVERRIED_PAIR_(*)
OPERATOR_OVERRIED_PAIR_(/)
OPERATOR_OVERRIED_PAIR_(%)

#undef OPERATOR_OVERRIED_PAIR_


template <class Ch, class Tr, class Tp, class Up>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, std::pair<Tp, Up> &p) { return is >> p.first >> p.second; }
template <class Ch, class Tr, class Tp, class Up>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os, const std::pair<Tp, Up> &p) { return os << p.first << ' ' << p.second; }
template <class Ch, class Tr, class Tp, class Up, class Vp>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, std::tuple<Tp, Up, Vp> &p) { return is >> std::get<0>(p) >> std::get<1>(p) >> std::get<2>(p); }
template <class Ch, class Tr, class Tp, class Up, class Vp>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os, const std::tuple<Tp, Up, Vp> &p) { return os << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p); }
template <class Ch, class Tr, class Tp, class Up, class Vp, class Wp>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, std::tuple<Tp, Up, Vp, Wp> &p) { return is >> std::get<0>(p) >> std::get<1>(p) >> std::get<2>(p) >> std::get<3>(p); }
template <class Ch, class Tr, class Tp, class Up, class Vp, class Wp>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os, const std::tuple<Tp, Up, Vp, Wp> &p) { return os << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p) << ' ' << std::get<3>(p); }


template <class Tp>
using pi = std::pair<Tp, Tp>;
template <class Tp>
using pi3 = std::tuple<Tp, Tp, Tp>;
template <class Tp>
using pi4 = std::tuple<Tp, Tp, Tp, Tp>;
template <class Tp>
using vc = std::vector<Tp>;
template <class Tp>
using vvc = std::vector<std::vector<Tp>>;
template <class Tp>
using pq = std::priority_queue<Tp>;
template <class Tp>
using pqg = std::priority_queue<Tp, std::vector<Tp>, std::greater<Tp>>;
template <class Tp>
using hset = std::unordered_set<Tp>;
template <class Key, class Tp, class Hash = std::hash<Key>>
using hmap = std::unordered_map<Key, Tp, Hash>;

using compi = std::complex<int>;
using compi64 = std::complex<i64>;
using compd = std::complex<double>;
using pii = pi<int>;
using pii64 = pi<i64>;
using pi3i = pi3<int>;
using pi3i64 = pi3<i64>;
using pi4i = pi4<int>;
using pi4i64 = pi4<i64>;

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
#define range_(a, l, r) (a).begin() + (l), (a).begin() + (r)
#define all_(a) (a).begin(), (a).end()
#define rrange_(a, l, r) (a).rbegin() + (l), (a).rbegin() + (r)
#define rall_(a) (a).rbegin(), (a).rend()
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
    fast_in.read(name)
#define read_container_(type, name, size) \
    type name(size);                      \
    foreach_ref_(i, name) fast_in.read(i)

template <class Tp>
auto chkmin(Tp &a, Tp b) -> bool { return b < a ? a = b, true : false; };
template <class Tp>
auto chkmax(Tp &a, Tp b) -> bool { return a < b ? a = b, true : false; };
template <class Tp>
auto discretization(Tp &var) -> Tp {
    Tp d__(var);
    std::sort(d__.begin(), d__.end());
    d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
    for (auto &i : var) i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
    return d__;
};
template <class Tp>
auto ispow2(Tp i) -> bool { return i && (i & -i) == i; }

template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) { return os << p.first << " " << p.second; }
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os, const Container &x) {
#ifdef LOCAL_
    if (&os == &std::cerr) os << "[";
    if (&os == &std::cerr)
        for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", ";
    else
#endif
        for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
    os << x.back();
#ifdef LOCAL_
    if (&os == &std::cerr) os << "]";
#endif
    return os;
}

template <class Tp>
inline void debug(Tp x) {
#ifdef LOCAL_
    std::cerr << x << std::endl;
#endif
}
template <class Tp, class... Args>
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
    int i_ = STATIC__;

#ifdef MULTI_CASES
    int t_;
    fast_in.read(t_);
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