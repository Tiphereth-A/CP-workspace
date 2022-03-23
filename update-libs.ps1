# !bin/sh

git submodule update --remote
rm -Recurse -Force ./tools/lib-cpp/atcoder
cp -Recurse ./lib/ac-library/atcoder ./tools/lib-cpp/atcoder
