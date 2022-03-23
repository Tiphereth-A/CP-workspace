#pragma once

namespace my_template {
#include <cstddef>
#include <iostream>

template <size_t _Edge_len, size_t _Node_size>
class DLX_base {
  protected:
    struct Node {
        size_t l, r, u, d;
        size_t row, col;
    } node[_Node_size + _Edge_len];
    size_t width, height;
    size_t cnt_node;

    size_t cnt_col[_Edge_len];

#define _l(id) node[id].l
#define _r(id) node[id].r
#define _u(id) node[id].u
#define _d(id) node[id].d
#define _row(id) node[id].row
#define _col(id) node[id].col
#define _for(i, start, dir) for (size_t i = _##dir(start); i != start; i = _##dir(i))

    void remove_col(size_t _now_col) {
        _r(_l(_now_col)) = _r(_now_col);
        _l(_r(_now_col)) = _l(_now_col);
        _for(i, _now_col, d) _for(j, i, r) {
            _u(_d(j)) = _u(j);
            _d(_u(j)) = _d(j);
            --cnt_col[_col(j)];
        }
    }
    void resume_col(size_t _now_col) {
        _r(_l(_now_col)) = _l(_r(_now_col)) = _now_col;
        _for(i, _now_col, u) _for(j, i, r) {
            _u(_d(j)) = _d(_u(j)) = j;
            ++cnt_col[_col(j)];
        }
    }

    size_t find_min_col() {
        size_t res = _r(0);
        _for(i, 0, r) if (cnt_col[i] < cnt_col[res]) res = i;
        return res;
    }

    virtual bool dance(size_t* _ans, size_t& _len) {
        if (_r(0) == 0) return true;
        size_t now_r = find_min_col();
        remove_col(now_r);
        _for(i, now_r, d) {
            _ans[++_len] = _row(i);
            _for(j, i, r) remove_col(_col(j));
            if (dance(_ans, _len)) {
                _for(j, i, l) resume_col(_col(j));
                return true;
            }
            --_len;
            _for(j, i, l) resume_col(_col(j));
        }
        resume_col(now_r);
        return false;
    }

  public:
    void debug() {
        std::cerr << "w: " << width << ", h: " << height << ", cnt: " << cnt_node << std::endl;
        std::cerr << "cnt_col: ";
        for (size_t i = 1; i <= width; ++i) std::cerr << cnt_col[i] << " ";
        std::cerr << std::endl;
        for (size_t i = 0; i <= cnt_node; ++i) std::cerr << "id: " << i << "; |" << node[i].l << "|" << node[i].r << "|" << node[i].u << "|" << node[i].d << "|" << node[i].row << "|" << node[i].col << "|" << std::endl;
        std::cerr << std::endl;
    }

  public:
    void clear() {
        memset(node, 0, sizeof(node));
        memset(cnt_col, 0, sizeof(cnt_col));
        width = height = cnt_node = 0;
    }

    void init(size_t _width, size_t _height) {
        width = cnt_node = _width;
        height = _height;
        for (size_t i = 1; i <= width; ++i) node[i] = {i - 1, i + 1, i, i, 0, i};
        node[_r(width) = 0] = {width, 1, 0, 0, 0, 0};
    }

    void insert_row(size_t _ln, size_t* const _cols, size_t _len_cols) {
        for (size_t i = 1; i <= _len_cols; ++i) {
            node[cnt_node + i] = {cnt_node + i - 1, cnt_node + i + 1, _u(_cols[i]), _cols[i], _ln, _cols[i]};
            _d(_u(_cols[i])) = cnt_node + i;
            _u(_cols[i]) = cnt_node + i;
            ++cnt_col[_cols[i]];
            if (_d(_cols[i]) == _cols[i]) _d(_cols[i]) = cnt_node + i;
        }
        _l(cnt_node + 1) = cnt_node + _len_cols;
        _r(cnt_node + _len_cols) = cnt_node + 1;
        cnt_node += _len_cols;
    }
    void insert_map(bool** const _map, size_t _width, size_t _height, size_t _height_phy = _Edge_len) {
        size_t* _ = (size_t*)malloc(sizeof(size_t) * (_width + 1));
        for (size_t _ln = 1, len; _ln <= _height; ++_ln) {
            len = 0;
            for (size_t _col = 1; _col <= _width; ++_col)
                if (*((bool*)_map + _ln * _height_phy + _col)) _[++len] = _col;
            if (len) insert_row(_ln, _, len);
        }
        free(_);
    }
    auto operator()(size_t* ans, size_t& len) {
        len = 0;
        return dance(ans, len);
    }
    // friend void test();

#undef _l
#undef _r
#undef _u
#undef _d
#undef _row
#undef _col
#undef _for
};

} // namespace my_template