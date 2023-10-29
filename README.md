# CP-workspace

![GitHub](https://img.shields.io/github/license/Tiphereth-A/CP-workspace)

My VSCode workspace for Competitive Programming. **Only for Linux**

## Features

- C++ Compile & Debug
- Useful C++ code snippets (see [Snippets](#Snippets))
- Useful tools
  - Local judger
  - ~~C++ lib expander~~ (use `oj-bundle` from [online-judge-tools/verification-helper](https://github.com/online-judge-tools/verification-helper) instead)
  - ~~C++ macro expander~~ (lack of maintenance)
- Including third C++ library support (see [Third library support](#Third%20library%20support))

## Usage

- Install [VSCode](https://code.visualstudio.com/) and [GCC](https://gcc.gnu.org/)
- Install VSCode extensions listed in `.vscode/extensions.json` (DO NOT use IntelliSense from `ms-vscode.cpptools`)
- (Optional) You can add key bindings by copying the contents of `.vscode/keybindings.json` into your `keybindings.json`

```bash
# Clone repo
git clone --recursive git@github.com:Tiphereth-A/CP-workspace.git

# Fix paths
cd CP-workspace
mkdir bin
touch data/in.in

# Run VSCode
code .

# Compile and run main.cpp
./tools/run_cpp.sh . main ./data
# Compile and run pmain.cpp
./tools/run_cpp.sh . pmain ./data
```

## Snippets

| name                             | prefix                                                   | introduction                        |
| -------------------------------- | -------------------------------------------------------- | ----------------------------------- |
| 2-sat                            | `2-sat`, `sat`, `sat-2`                                  |
| bitset-AVX                       | `bitset-avx`                                             | bitset under AVX                    |
| bipartitle-graph-coloring        | `bipartitle-graph-coloring`                              |
| chtholly                         | `chtholly-tree`, `old-driver-tree`                       |
| euler-path-graph                 | `euler-path-graph`                                       | Find Euler path (undirection graph) |
| euler-path-digraph               | `euler-path-digraph`                                     | Find Euler path (digraph)           |
| foreach                          | `fors`, `foreach`                                        | Some for macros                     |
| gcc-temp-ignore-warning          | `gcc-ignore-warning`, `ignore-warning`                   |
| graph                            | `graph`, `edges`                                         | Adjacency list                      |
| hoverline                        | `hoverline`                                              |
| init-cpp-simple                  | `iis`, `init-simple`                                     |
| johnson                          | `johnson`                                                |
| KMP-FFT                          | `kmp-fft`, `fft-kmp`                                     |
| lagrange-interpolation-fixed-key | `lagrange-interpolation-fixed-key`                       |
| persistable-segtree              | `psegtree`, `p-segtree`                                  |
| sqrt-bucket                      | `blocking`, `sqrt-blocking`, `sqrt-bucket`               |
| stdc++11                         | `stdc++11`                                               | Standard libs (C++11)               |
| stdc++98                         | `stdc++98`                                               | Standard libs (C++98)               |
| suffix-array                     | `sa`, `suffix-array`                                     |
| tree-hash-rooted                 | `rooted-tree-hash`, `tree-hash-rooted`                   |
| tree-hash-unrooted               | `unrooted-tree-hash`, `tree-hash-unrooted`               |
| treap-no-rotate                  | `fhqtreap`, `treap-nr`, `treap-no-rotate`                | FHQTreap (rank)                     |
| treap-no-rotate-flip             | `fhqtreap-flip`, `treap-nr-flip`, `treap-no-rotate-flip` | FHQTreap (flip)                     |
| Trie                             | `trie`                                                   |
| UDHeap                           | `udheap`                                                 |

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
