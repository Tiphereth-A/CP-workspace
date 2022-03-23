#pragma once

namespace my_template {
#include <cstddef>

template <size_t _Edge_len, size_t _Node_size>
class multi_DLX {
  private:
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
#define for_(i, start, dir) for (size_t i = _##dir(start); i != start; i = _##dir(i))

    void remove_col(size_t _now_col) {
        for_(i, _now_col, d) {
            _r(_l(i)) = _r(i);
            _l(_r(i)) = _l(i);
        }
    }

    void resume_col(size_t _now_col) {
        for_(i, _now_col, u)
            _r(_l(i)) = _l(_r(i)) = i;
    }

    size_t find_min_col() {
        size_t res = _r(0);
        for_(i, 0, r) if (cnt_col[i] < cnt_col[res]) res = i;
        return res;
    }

    bool vis[_Edge_len];
    size_t H() {
        size_t ret = 0;
        memset(vis, 0, sizeof(vis));
        for_(i, 0, r) {
            if (vis[i]) continue;
            ++ret;
            vis[i] = true;
            for_(j, i, d) for_(k, j, r) vis[_col(k)] = true;
        }
        return ret;
    }

    bool dance(size_t* _ans, size_t& _ans_len, size_t max_depth, size_t now_depth = 1) {
        if (now_depth > max_depth) return false;
        if (_r(0) == 0) return true;
        size_t now_col = find_min_col();
        if (now_depth + H() > max_depth) return false;
        for_(i, now_col, d) {
            remove_col(i);
            _ans[++_ans_len] = _row(i);
            for_(j, i, r) remove_col(j);
            if (dance(_ans, _ans_len, max_depth, now_depth + 1)) {
                for_(j, i, l) resume_col(j);
                resume_col(i);
                return true;
            }
            --_ans_len;
            for_(j, i, l) resume_col(j);
            resume_col(i);
        }
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

    size_t operator()(size_t* ans) {
        size_t len = 0, _ = 0;
        size_t l = 1, r = height, mid;
        while (l <= r) {
            mid = l + ((std::ptrdiff_t)r - l) / 2;
            _ = 0;
            if (dance(ans, _, mid)) {
                len = _;
                r = _ - 1;
            } else
                l = mid + 1;
        }
        return len;
    }
    // friend void test();

#undef _l
#undef _r
#undef _u
#undef _d
#undef _row
#undef _col
#undef for_
};

} // namespace my_template