#pragma once

namespace my_template {
#include <cstddef>
#include <cstdlib>

namespace AC_automaton {
template <size_t _N, typename Tp, char _str_begin, char _str_end, bool _clear>
class _ACAM_Base {
  protected:
    struct ACAM_t {
        size_t next[_str_end - _str_begin];
        size_t fail;
        bool end;
    };

    size_t cnt_data;
    bool builded;
    ACAM_t data[_N];

  private:
    virtual void _insert_end(size_t p, size_t x) { data[p].end = true; };
    virtual void _query_mid(Tp& res, size_t p) = 0;
    virtual void _query_end(Tp& res) {}

  public:
    _ACAM_Base() {
        cnt_data = builded = 0;
        if (_clear) memset(data, 0, sizeof(data));
    }

    virtual void clear() {
        cnt_data = builded = 0;
        memset(data, 0, sizeof(data));
    }
    void insert(const std::string_view& str, size_t x = 0) {
        size_t p = 0;
        for (size_t i = 0, c; i < str.size(); ++i) {
            if (!data[p].next[c = str[i] - _str_begin]) data[p].next[c] = ++cnt_data;
            p = data[p].next[c];
        }
        _insert_end(p, x);
    }
    void build() {
        std::queue<size_t> q;
        for (size_t i : data[0].next)
            if (i) q.push(i);
        size_t p = 0;
        while (!q.empty()) {
            p = q.front();
            q.pop();
            for (size_t i = 0; i < _str_end - _str_begin; ++i) {
                if (data[p].next[i]) {
                    data[data[p].next[i]].fail = data[data[p].fail].next[i];
                    q.push(data[p].next[i]);
                } else
                    data[p].next[i] = data[data[p].fail].next[i];
            }
        }
        builded = true;
    }
    Tp query(const std::string_view& str) {
        if (!builded) build();
        size_t p = 0;
        Tp res = 0;
        for (char c : str) _query_mid(res, p = data[p].next[c - _str_begin]);
        _query_end(res);
        return res;
    }
};

//! Change this when using
template <size_t _N, typename Tp, char _str_begin = 'a', char _str_end = 'z' + 1, bool _clear = false>
class ACAM : public _ACAM_Base<_N, Tp, _str_begin, _str_end, _clear> {
  protected:
    Tp e[_N];

  private:
    void _insert_end(size_t p, size_t x) {
        this->data[p].end = true;
        ++e[p];
    }
    void _query_mid(Tp& res, size_t p) {
        for (size_t i = p; i && ~e[i]; i = this->data[i].fail) {
            res += e[i];
            e[i] = -1;
        }
    };
    void _query_end(Tp& res){};

  public:
    ACAM() {
        if (_clear) memset(e, 0, sizeof(e));
    }

    void clear() {
        this->cnt_data = this->builded = 0;
        memset(this->data, 0, sizeof(this->data));
        memset(e, 0, sizeof(e));
    }
};
} // namespace AC_automaton
using AC_automaton::ACAM;

} // namespace my_template