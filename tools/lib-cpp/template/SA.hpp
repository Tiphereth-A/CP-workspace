#pragma once

namespace my_template {
#include <algorithm>
#include <cstddef>
#include <functional>
#include <random>

namespace Simulated_annealing {

//! --- config ---

using data_type = int64_t;
using fit_type = double;
using index_type = size_t;
using temperature_type = double;
template <class Tp>
using seq_type = std::vector<Tp>;
using data_seq_type = seq_type<data_type>;
using fit_seq_type = seq_type<fit_type>;

std::default_random_engine g(time(nullptr));
std::uniform_int_distribution<data_type> data_gen;
std::uniform_int_distribution<index_type> idx_gen;
std::uniform_real_distribution<temperature_type> p_gen(0, 1);

const temperature_type delta_T = 0.99;
const temperature_type initial_T = 5000;
const temperature_type minimum_T = 1e-8;

//! edit this function, or SA can't work
fit_type fitness(const data_seq_type& seq) { return 0; }

//! keep this if the sequence don't need to be checked
constexpr bool is_valid_seq(const data_seq_type& seq) { return true; }

//! --- config end ---

data_seq_type new_seq_shuffle(const data_seq_type& seq) {
    data_seq_type ret(seq);
    do { std::shuffle(ret.begin(), ret.end(), g); } while (!is_valid_seq(ret));
    return ret;
}

data_seq_type new_seq_generate(const data_seq_type&& minimum, const data_seq_type&& maximum) {
    data_seq_type ret;
    do {
        ret.clear();
        for (auto i = minimum.begin(), j = maximum.begin(); i != minimum.end() && j != maximum.end(); ++i, ++j) ret.push_back(data_gen(g) % (*j - *i) + *i);
    } while (!is_valid_seq(ret));
    return ret;
}

data_seq_type new_seq_generate_n(const data_type&& minimum, const data_type&& maximum, const index_type&& n) {
    data_seq_type ret;
    ret.resize(n);
    do {
        for (index_type i = 0; i < n; ++i) ret[i] = data_gen(g) % (maximum - minimum) + minimum;
    } while (!is_valid_seq(ret));
    return ret;
}

void swap_two_elements(data_seq_type& seq, const index_type& x, const index_type& y) { iter_swap(seq.begin() + x, seq.begin() + y); }

std::pair<index_type, index_type> swap_two_elements_randomly(data_seq_type& seq) {
    index_type x, y;
    do {
        x = idx_gen(g) % seq.size();
        y = idx_gen(g) % seq.size();
    } while (x == y);
    swap_two_elements(seq, x, y);
    return {x, y};
}

//? Metropolis acceptance criteria
bool accept(const fit_type& delta_fitness, const temperature_type& now_T) { return delta_fitness <= 0 || exp(-delta_fitness / now_T) > p_gen(g); }

// find minimum for fitness(sequence), which sequence is a permutation of initial_sequence
fit_type main_seq(data_seq_type& ans_seq) {
    // data_seq_type now_seq;
    fit_type ans = fitness(ans_seq), now_ans;
    index_type x, y;
    for (temperature_type T = initial_T; T > minimum_T; T *= delta_T) {
        std::tie(x, y) = swap_two_elements_randomly(ans_seq);
        now_ans = fitness(ans_seq);
        if (accept(now_ans - ans, T))
            ans = now_ans;
        else
            swap_two_elements(ans_seq, x, y);

        //? you can also use these below instead if you want the sequence changes more rapidly
        // now_seq = new_seq_shuffle(ans_seq);
        // now_ans = fitness(ans_seq);
        // if (accept(now_ans - ans, T)) {
        //     ans = now_ans;
        //     ans_seq = now_seq;
        // }
    }
    return ans;
}

// find minimum for fitness(sequence), which sequence[i] in [minimum[i], maximum[i])
fit_type main_range(const data_seq_type&& minimum, const data_seq_type&& maximum) {
    data_seq_type ans_seq(new_seq_generate(std::move(minimum), std::move(maximum))), now_seq;
    fit_type ans = fitness(ans_seq), now_ans;
    for (temperature_type T = initial_T; T > minimum_T; T *= delta_T) {
        now_seq = new_seq_generate(std::move(minimum), std::move(maximum));
        now_ans = fitness(now_seq);
        if (accept(now_ans - ans, T)) {
            ans = now_ans;
            ans_seq = now_seq;
        }
    }
    return ans;
}

// find minimum for fitness(sequence), which sequence[0..n-1] in [minimum, maximum)
fit_type main_range_n(const data_type&& minimum, const data_type&& maximum, const index_type&& n) {
    data_seq_type ans_seq(new_seq_generate_n(std::move(minimum), std::move(maximum), std::move(n))), now_seq;
    fit_type ans = fitness(ans_seq), now_ans;
    for (temperature_type T = initial_T; T > minimum_T; T *= delta_T) {
        now_seq = new_seq_generate_n(std::move(minimum), std::move(maximum), std::move(n));
        now_ans = fitness(now_seq);
        if (accept(now_ans - ans, T)) {
            ans = now_ans;
            ans_seq = now_seq;
        }
    }
    return ans;
}

} // namespace Simulated_annealing
using Simulated_annealing::main_range;
using Simulated_annealing::main_range_n;
using Simulated_annealing::main_seq;

} // namespace my_template