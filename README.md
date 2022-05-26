# CP-workspace

![GitHub](https://img.shields.io/github/license/Tiphereth-A/CP-workspace)

My VSCode workspace for Competitive Programming.

## Features

-   C++ Compile & Debug
-   Useful C++ code snippets (see [Snippets](#Snippets))
-   Useful tools
    -   Testcase generator & wrapper
    -   Local judger
    -   C++ lib expander (inspired by [atcoder/ac-Library](https://github.com/atcoder/ac-library))
    -   C++ macro expander (lack of maintenance)
-   Including 3rd C++ library support (see [3rd library support](#3rd%20library%20support))

## Usage

-   Install VSCode and GCC (MinGW, Cygwin, ...)
-   Clone this repo.
-   Add environment `CPPBIN_PATH`, set the value to C++ compiler directory.
-   Add environment `CPPDBG_PATH`, set the value to C++ debugger directory.
-   Add environment `CPPLIB_PATH`, set the value to C++ standard library directory.
-   Open this folder with VSCode
-   (Optional) You can add key bindings by copying the contents of `.vscode/keybindings.json` into your `keybindings.json`.
-   Enjoy!

## Snippets

| name                  | prefix                                                             | introduction                                            |
| --------------------- | ------------------------------------------------------------------ | ------------------------------------------------------- |
| init-cpp-simple       | `iis`, `init_simple`                                               |
| init-cpp              | `ii`, `init`                                                       |
| foreach               | `fors`, `foreach`                                                  | Some for macros                                         |
| ostream-int128        | `os128`, `out128`, `cout128`                                       | `__int128_t` and `___uint128_t` support for `std::cout` |
| fast-IO               | `fastIO`                                                           | Fast IO based on `fread` & `fwrite`                     |
| untie                 | `fast_ios`, `fast_cin_cout`                                        |
| fast-max              | `max_fast`, `fast_max`                                             |
| fast-min              | `min_fast`, `fast_min`                                             |
| fast-str2uint         | `str2uint_fast`, `dec2uint_fast`, `fast_str2uint`, `fast_dec2uint` |
| combination           | `comb`, `combination`, `m_choose_n`                                |
| factorial-and-inverse | `fact`, `factorial`                                                |
| gcd-lambda            | `gcd_lambda`                                                       |
| exgcd                 | `exgcd`                                                            |
| qwick-pow             | `qpow`                                                             |
| mul_mod               | `mul_mod`                                                          |
| pow_mod               | `pow_mod`                                                          |
| euler_phi             | `phi`, `euler_phi`                                                 |
| inverse               | `inv`, `inverse`                                                   |
| prime                 | `prime`                                                            | Euler seive                                             |
| rpow                  | `rpow`                                                             |
| graph                 | `graph`, `edges`                                                   | Adjacency list                                          |
| dijkstra              | `dijkstra`, `dijk`                                                 |
| kruakal               | `kruskal`                                                          |
| johnson               | `johnson`                                                          |
| tarjan-scc            | `scc`, `tarjan-scc`                                                | Find all SCC based on Tarjan algorithm                  |
| 2-sat                 | `2_sat`, `sat`, `sat_2`                                            |
| euler-path-graph      | `euler_path_graph`                                                 | Find Euler path (undirection graph)                     |
| euler-path-digraph    | `euler_path_digraph`                                               | Find Euler path (digraph)                               |
| dsu-basic             | `dsu_basic`                                                        | DSU                                                     |

## 3rd library support

Copy your library to `tools\lib-cpp` and start using it!

Example:

-   [AC-library](https://github.com/atcoder/ac-library)

    ```cpp
    #include <iostream>
    #include <atcoder/convolution.hpp>

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
