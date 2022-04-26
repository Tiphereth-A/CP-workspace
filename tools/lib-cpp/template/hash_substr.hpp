#pragma once

namespace my_template {
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

template <uint64_t BASE, uint64_t MOD, char _start = 'a'>
class Hash_substr {
  protected:
    std::vector<uint64_t> hash, p;

  public:
    Hash_substr(const std::string_view& _str) {
        hash.push_back(0);
        p.push_back(1);
        for (char ch : _str) {
            hash.push_back((hash.back() * BASE % MOD + ch - _start + 1) % MOD);
            p.push_back(p.back() * BASE % MOD);
        }
    }
    //! [l, r), l start at 0
    uint64_t operator()(size_t l, size_t r) const { return (hash[r] - (int64_t)hash[l] * p[r - l] % MOD + MOD) % MOD; }
};
} // namespace my_template