#pragma once

namespace my_template {
#include <cstddef>

template <size_t _CHILD, size_t N, typename Tp = size_t, bool _clear = false>
class Huffman_tree {
  protected:
    struct Node {
        Tp w;
        size_t child[_CHILD];
        size_t cnt_child;
    } nodes[N];
    bool _build;
    size_t cnt_nodes, max_child_size, leaves;

  public:
    Huffman_tree(size_t max_child = 2) : max_child_size(max_child) {
        if (_clear) this->clear();
    }
    void clear() { memset(nodes, cnt_nodes = leaves = max_child_size = _build = 0, sizeof(nodes)); }

    void build(const vector<Tp>& frenqucy, size_t max_child) {
        if (_build) return;
        max_child_size = max_child;
        cnt_nodes = frenqucy.size();
        for (size_t i = 1; i <= cnt_nodes; ++i) {
            nodes[i].w = frenqucy[i - 1];
            nodes[i].cnt_child = 0;
        }
        cnt_nodes += ((max_child - 1) - ((cnt_nodes - 1) % (max_child - 1))) % (max_child - 1);

        priority_queue<pair<Tp, int>, vector<pair<Tp, int>>, greater<pair<Tp, int>>> q;
        for (size_t i = 1; i <= cnt_nodes; ++i) q.emplace(nodes[i].w, i);
        while (q.size() > 1) {
            ++cnt_nodes;
            for (size_t i = 1; i <= max_child_size; ++i) {
                if (q.empty()) break;
                nodes[cnt_nodes].w += q.top().first;
                nodes[cnt_nodes].child[++nodes[cnt_nodes].cnt_child] = q.top().second;
                q.pop();
            }
            q.emplace(nodes[cnt_nodes].w, cnt_nodes);
        }
        _build = 1;
    }

    // encode(frenqucy, char_set)[i] means the Huffman code of frenqucy[i]
    vector<string> encode(const vector<Tp>& frenqucy, const string& char_set = "01") {
        if (!_build) build(frenqucy, char_set.length());
        vector<string> ret;
        ret.resize(frenqucy.size());
        queue<pair<size_t, string>> q;
        q.emplace(cnt_nodes, "");
        while (!q.empty()) {
            pair<size_t, string> now = q.front();
            q.pop();
            const Node& now_node = nodes[now.first];
            for (size_t i = 1; i <= now_node.cnt_child; ++i) {
                const Node& next_node = nodes[now_node.child[i]];
                if (next_node.cnt_child == 0) {
                    if (now_node.child[i] <= ret.size()) ret[now_node.child[i] - 1] = now.second + char_set[i - 1];
                    continue;
                } else
                    q.emplace(now_node.child[i], now.second + char_set[i - 1]);
            }
        }
        return ret;
    }

    // get_depth(frenqucy, max_child)[i] means the length of frenqucy[i]'s Huffman code
    vector<size_t> get_depth(const vector<Tp>& frenqucy, const size_t max_child = 2) {
        if (!_build) build(frenqucy, max_child);
        vector<size_t> ret;
        ret.resize(frenqucy.size());
        queue<pair<size_t, size_t>> q;
        q.emplace(cnt_nodes, 0);
        while (!q.empty()) {
            pair<size_t, size_t> now = q.front();
            q.pop();
            const Node& now_node = nodes[now.first];
            for (size_t i = 1; i <= now_node.cnt_child; ++i) {
                const Node& next_node = nodes[now_node.child[i]];
                if (next_node.cnt_child == 0) {
                    if (now_node.child[i] <= ret.size()) ret[now_node.child[i] - 1] = now.second + 1;
                    continue;
                } else
                    q.emplace(now_node.child[i], now.second + 1);
            }
        }
        return ret;
    }
};

} // namespace my_template