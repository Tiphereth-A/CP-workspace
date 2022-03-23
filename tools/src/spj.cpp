#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)

const int N = 1e5 + 5;

const std::size_t ACCEPT            = 0;
const std::size_t WRONG_ANSWER      = 1;
const std::size_t TIME_LIMIT_EXCEED = 2;

int main(int argc, char ** argv) {
    if (argc < 4) throw invalid_argument("in, out, ans required");
    ifstream in(argv[1]), out(argv[2]), ans(argv[3]);

    char ch_out, ch_ans;
    while (out && ans) {
        out >> ch_out;
        ans >> ch_ans;
        if (ch_out != ch_ans) return WRONG_ANSWER;
    }

    if (out || ans) return WRONG_ANSWER;
    return ACCEPT;
}