#include <vector>
#include <cstddef>
#include <cstdint>

void radix_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  std::vector<int> output(n);
  constexpr std::size_t kRadix = 256;

  for (int pass = 0; pass < 4; ++pass) {
    std::size_t count[kRadix] = {};
    const int shift = pass * 8;

    for (int value : values) {
      const std::uint32_t key = static_cast<std::uint32_t>(value) ^ 0x80000000u;
      const std::size_t bucket = (key >> shift) & 0xFFu;
      ++count[bucket];
    }

    for (std::size_t i = 1; i < kRadix; ++i) {
      count[i] += count[i - 1];
    }

    for (std::size_t i = n; i-- > 0;) {
      const std::uint32_t key = static_cast<std::uint32_t>(values[i]) ^ 0x80000000u;
      const std::size_t bucket = (key >> shift) & 0xFFu;
      output[--count[bucket]] = values[i];
    }

    values.swap(output);
  }
}
