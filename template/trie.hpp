#pragma once

namespace my_template {
#include <cstddef>

template <size_t _N, char _str_begin = 'a', char _str_end = 'z' + 1, bool _clear = false>
class Trie {
  protected:
    struct trie_t {
        size_t next[_str_end - _str_begin];
        bool end;
    };

    size_t cnt_data;
    trie_t data[_N];

  public:
    Trie() {
        if (_clear) this->clear();
    }

    void clear() { memset(data, cnt_data = 0, sizeof(data)); }
    void insert(const string& str) {
        size_t p = 0;
        for (size_t i = 0, c; i < str.size(); ++i) {
            if (!data[p].next[c = str[i] - _str_begin]) data[p].next[c] = ++cnt_data;
            p = data[p].next[c];
        }
        data[p].end = true;
    }
    bool query(const string& str) {
        size_t p = 0;
        for (size_t i = 0, c; i < str.size(); ++i) {
            if (!data[p].next[c = str[i] - _str_begin]) return false;
            p = data[p].next[c];
        }
        return data[p].end;
    }
};

} // namespace my_template