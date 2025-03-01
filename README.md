# CP-workspace

![GitHub](https://img.shields.io/github/license/Tiphereth-A/CP-workspace)

My VSCode workspace for Competitive Programming. **Only for Linux**

## Features

- C++ Compile & Debug
- Useful C++ code snippets (see [Snippets](#Snippets))

  NOTE: most of snippets have been moved to [Tiphereth-A/CP-lib](https://github.com/Tiphereth-A/CP-lib).

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
git clone --recurse-submodules git@github.com:Tiphereth-A/CP-workspace.git

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

| name               | prefix                                 | introduction          |
| ------------------ | -------------------------------------- | --------------------- |
| gcc-ignore-warning | `gcc-ignore-warning`, `ignore-warning` |
| KMP-FFT            | `kmp-fft`, `fft-kmp`                   |
| stdc++11           | `stdc++11`                             | Standard libs (C++11) |
| stdc++98           | `stdc++98`                             | Standard libs (C++98) |

## Third library support

Copy your library to `lib` and start using it!

Example:

- [ac-library](https://github.com/atcoder/ac-library)

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

- [CP-lib](https://github.com/Tiphereth-A/CP-lib) from myself
- [dbg-macro](https://github.com/sharkdp/dbg-macro)
- [magic-cpp](https://github.com/16bit-ykiko/magic-cpp)
- [testlib](https://github.com/MikeMirzayanov/testlib)
