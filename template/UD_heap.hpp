#pragma once

namespace my_template {
#include <cstddef>
#include <queue>

template <class Tp>
class UD_heap {
  private:
    std::priority_queue<Tp> dq;
    std::priority_queue<Tp, std::vector<Tp>, std::greater<Tp>> uq;
    bool _init = 0;

  public:
    void clear() {
        _init = 0;
        dq = decltype(dq)();
        uq = decltype(uq)();
    }
    void init(Tp x) {
        if (_init) {
            insert(x);
            return;
        }
        dq.push(x);
        _init = 1;
    }
    void insert(Tp x) {
        if (!_init) {
            init(x);
            return;
        }
        (x > dq.top() ? uq.push(x) : dq.push(x));
        if (uq.size() > dq.size() + 1) {
            dq.push(uq.top());
            uq.pop();
        } else if (dq.size() > uq.size() + 1) {
            uq.push(dq.top());
            dq.pop();
        }
    }
    Tp get_mid() { return uq.size() > dq.size() ? uq.top() : dq.top(); }
};

} // namespace my_template