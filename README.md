# CP-workspace

![GitHub](https://img.shields.io/github/license/Tiphereth-A/CP-workspace)

My VSCode workspace for Competitive Programming. **Only for Linux**

## Features

- C++ Compile & Debug
- Useful C++ code snippets (see [Snippets](#Snippets))
- Useful tools
  - Local judger
  - C++ lib expander (inspired by [atcoder/ac-Library](https://github.com/atcoder/ac-library))
  - ~~C++ macro expander~~ (lack of maintenance)
- Including third C++ library support (see [Third library support](#Third%20library%20support))

## Usage

- Install [VSCode](https://code.visualstudio.com/) and [GCC](https://gcc.gnu.org/)
- (Optional) You can add key bindings by copying the contents of `.vscode/keybindings.json` into your `keybindings.json`

```bash
# Clone repo
git clone git@github.com:Tiphereth-A/CP-workspace.git

# Fix paths
cd CP-workspace
mkdir bin
touch data/in.in

# Install submodules
git submodule update --init

# Run VSCode
code .

# Compile and run main.cpp
./tools/run_cpp.sh . main ./data
# Compile and run pmain.cpp
./tools/run_cpp.sh . pmain ./data
```

## Snippets

| name                                | prefix                                                   | introduction                                                                                               |
| ----------------------------------- | -------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| 2-sat                               | `2-sat`, `sat`, `sat-2`                                  |
| balanced-tree-based-on-fenwick-tree | `bst-bit`, `bt-bit`                                      |
| binary-search                       | `binary-search`                                          |
| bitset-AVX                          | `bitset-avx`                                             | bitset under AVX                                                                                           |
| barrett                             | `barrett`                                                | Fast modular multiplication by barrett reduction                                                           |
| bsgs                                | `BSGS`, `EXBSGS`                                         |
| bellman-ford                        | `bellman-ford`, `spfa`, `bford`                          |
| bipartitle-graph-coloring           | `bipartitle-graph-coloring`                              |
| cantor-expansion                    | `cantor`, `cantor-exp`                                   |
| chtholly                            | `chtholly-tree`, `old-driver-tree`                       |
| combination                         | `comb`, `combination`, `m-choose-n`                      |
| convolution-fft                     | `conv`, `convolution`, `convolution-fft`, `fft-double`   |
| crt                                 | `crt`                                                    |
| dijkstra                            | `dijkstra`, `dijk`                                       |
| discretization                      | `discretization`                                         |
| DLX                                 | `dancing-link-x`, `dlx`                                  |
| dsu-basic                           | `dsu-basic`                                              |
| dsu-weighted                        | `dsu-weighted`                                           |
| enumerate-cpp17                     | `enumerate-cpp17`                                        | Implement of enumerate in C++17                                                                            |
| euler-path-graph                    | `euler-path-graph`                                       | Find Euler path (undirection graph)                                                                        |
| euler-path-digraph                  | `euler-path-digraph`                                     | Find Euler path (digraph)                                                                                  |
| euler-phi                           | `phi`, `euler-phi`                                       |
| excrt                               | `excrt`                                                  |
| exeuclid                            | `exeuclid`                                               |
| exgcd                               | `exgcd`                                                  |
| exlucas                             | `exlucas`                                                |
| factorial-and-inverse               | `fact`, `factorial`                                      |
| factors                             | `factors`                                                |
| fast-max                            | `max-fast`, `fast-max`                                   |
| fast-min                            | `min-fast`, `fast-min`                                   |
| fast-str2uint                       | `str2uint-fast`, `fast-str2uint`                         |
| floyd                               | `floyd`                                                  |
| foreach                             | `fors`, `foreach`                                        | Some for macros                                                                                            |
| fenwick-tree                        | `fenwick`, `fenwick-tree`                                |
| gauss-bitset                        | `gauss-bitset`                                           | Gauss' method on bool matrix                                                                               |
| gauss-int                           | `gauss-int`                                              | Gauss int $Z[\sqrt{-p}]$, $p>0$ (NO overflow protect)                                                      |
| gcc-temp-ignore-warning             | `gcc-ignore-warning`, `ignore-warning`                   |
| gcd-lambda                          | `gcd-lambda`                                             |
| gcd-O1                              | `gcd-O1`                                                 |
| gcd-real                            | `gcd-real`, `real-gcd`                                   |
| graph                               | `graph`, `edges`                                         | Adjacency list                                                                                             |
| gray-code                           | `gray-code`                                              |
| hash-splitmix64                     | `custom-hash`, `hash-splitmix64`                         | See [this blog](https://codeforces.com/blog/entry/62393)                                                   |
| hash-str                            | `hash-str`                                               | Rolling hash                                                                                               |
| hash-str2                           | `hash-str2`                                              | Rolling hash with 2 Modules                                                                                |
| hoverline                           | `hoverline`                                              |
| huffman-tree                        | `huffman`, `huffman-tree`                                |
| init-cpp-simple                     | `iis`, `init-simple`                                     |
| inverse                             | `inv`, `inverse`                                         |
| inverse-gcd                         | `inv-gcd`, `inverse-gcd`                                 |
| inverse-linear-gen                  | `linv-gen`, `inv-linear-gen`, `inverse-linear-gen`       |
| johnson                             | `johnson`                                                |
| KMP-FFT                             | `kmp-fft`, `fft-kmp`                                     |
| kruakal                             | `kruskal`                                                |
| lagrange-interpolation-fixed-key    | `lagrange-interpolation-fixed-key`                       |
| legendre-symbol                     | `legendre`, `legendre-symbol`                            |
| lucas                               | `lucas`                                                  | Calculating combination num using Lucas theorem                                                            |
| manacher                            | `manacher`                                               |
| matrix                              | `mat`, `mat`                                             |
| miller-rabin                        | `miller-rabin`, `is-prime`                               |
| mod-int                             | `mod-int`                                                |
| mul-mod                             | `mul-mod`                                                |
| ndvector                            | `ndvector`, `n-dim-vector`                               | See [this blog](https://blog.tifa-233.com/archives/draft-025/), use `std::mdspan` instead of this in C++23 |
| ostream-int128                      | `os128`, `out128`, `cout128`                             | `__int128_t` and `___uint128_t` support for `std::cout`                                                    |
| pair-useful-func                    | `pair-func`, `pair-useful-func`                          |
| persistable-segtree                 | `psegtree`, `p-segtree`                                  |
| pollard-rho                         | `pollard-rho`                                            |
| pow-mod                             | `pow-mod`                                                |
| prime                               | `prime`                                                  | Euler seive                                                                                                |
| prime-factors                       | `prime-factors`                                          |
| primitive-root-i32                  | `proot32`, `primitive-root-i32`                          |
| quad-residue                        | `quadr`, `quad-residue`                                  |
| qwick-pow                           | `qpow`                                                   |
| real-basis                          | `real-basis`                                             |
| reverse-cantor-expansion            | `rcantor`, `rcantor-exp`                                 |
| radix-sort-u32                      | `rsortu32`, `radix-sort-u32`                             |
| RMQ-ST                              | `rmq`, `rmq-st`                                          |
| RMQ-ST-2D                           | `rmq-2d`, `rmq-st-2d`                                    |
| rpow                                | `rpow`                                                   |
| romberg                             | `romberg`                                                | Romberg integration                                                                                        |
| safe-mod                            | `safe-mod`                                               |
| simpson                             | `simpson`                                                | Adaptive Simpson integration                                                                               |
| simpson-dep-limit                   | `simpson-with-min-depth-limit`                           | Slower but maybe more accurate for discret function                                                        |
| simulated-annealing                 | `simulated-annealing`                                    |
| sqrt-bucket                         | `blocking`, `sqrt-blocking`, `sqrt-bucket`               |
| stdc++11                            | `stdc++11`                                               | Standard libs (C++11)                                                                                      |
| stdc++98                            | `stdc++98`                                               | Standard libs (C++98)                                                                                      |
| Sudoku                              | `sudoku`                                                 |
| suffix-array                        | `sa`, `suffix-array`                                     |
| tarjan-scc                          | `scc`, `tarjan-scc`                                      | Find all SCC based on Tarjan algorithm                                                                     |
| Texas Hold'em Poker                 | `thpoker`, `texas`, `texas-holdem`, `texas-poker`        |
| tree-centroid                       | `centroid`, `tcent`, `tree-centroid`                     |
| tree-hash-rooted                    | `rooted-tree-hash`, `tree-hash-rooted`                   |
| tree-hash-unrooted                  | `unrooted-tree-hash`, `tree-hash-unrooted`               |
| treap-no-rotate                     | `fhqtreap`, `treap-nr`, `treap-no-rotate`                | FHQTreap (rank)                                                                                            |
| treap-no-rotate-flip                | `fhqtreap-flip`, `treap-nr-flip`, `treap-no-rotate-flip` | FHQTreap (flip)                                                                                            |
| Trie                                | `trie`                                                   |
| tuple-useful-func                   | `tuple-func`, `tuple-useful-func`                        | See [this blog](https://blog.tifa-233.com/archives/draft-020/)                                             |
| UDHeap                              | `udheap`                                                 |
| untie                               | `fast-ios`, `fast-cin-cout`                              |
| xor-basis                           | `xor-basis`                                              |

## Third library support

Copy your library to `lib` and start using it!

Example:

- [AC-library](https://github.com/atcoder/ac-library)

  ```cpp
  #include <iostream>
  #include "atcoder/convolution.hpp"

  int main() {
      for (auto i : atcoder::convolution_ll({1, 1, 4}, {5, 1, 4}))
          std::cout << i << std::endl;
      return 0;
  }
  ```

  output:

  ```text
  5
  6
  25
  8
  16
  ```
