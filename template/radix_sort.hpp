#pragma once

namespace my_template {
#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace radix_sort_u32 {
using data_type = uint32_t;
using size_type = uint32_t;
using pointer = data_type*;
using bucket = size_type[256];
bucket cnt0, cnt8, cnt16, cnt24;
constexpr void main(pointer a, size_type n) {
    pointer b = (pointer)malloc(n * sizeof(data_type));
    for (pointer _ = a + n, i = a; i < _; ++i) {
        ++cnt0[*i & 255];
        ++cnt8[*i >> 8 & 255];
        ++cnt16[*i >> 16 & 255];
        ++cnt24[*i >> 24 & 255];
    }
    for (size_type i = 1; i < 256; ++i) {
        cnt0[i] += cnt0[i - 1];
        cnt8[i] += cnt8[i - 1];
        cnt16[i] += cnt16[i - 1];
        cnt24[i] += cnt24[i - 1];
    }
    for (pointer i = a + n; --i >= a;) b[--cnt0[*i & 255]] = *i;
    for (pointer i = b + n; --i >= b;) a[--cnt8[*i >> 8 & 255]] = *i;
    for (pointer i = a + n; --i >= a;) b[--cnt16[*i >> 16 & 255]] = *i;
    for (pointer i = b + n; --i >= b;) a[--cnt24[*i >> 24 & 255]] = *i;
    free(b);
}
} // namespace radix_sort_u32

} // namespace my_template