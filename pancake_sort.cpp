#include <vector>
#include <cstddef>
#include <utility>
#include <algorithm>

namespace {
std::size_t find_max(const std::vector<int>& values, std::size_t until) {
  std::size_t max_idx = 0;
  for (std::size_t i = 1; i < until; ++i) {
    if (values[i] > values[max_idx]) {
      max_idx = i;
    }
  }
  return max_idx;
}

void flip(std::vector<int>& values, std::size_t until) {
  std::reverse(values.begin(), values.begin() + until);
}
}  // anonymous namespace

void pancake_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  for (std::size_t curr_size = n; curr_size > 1; --curr_size) {
    std::size_t max_idx = find_max(values, curr_size);
    if (max_idx == curr_size - 1) {
      continue;
    }
    if (max_idx != 0) {
      flip(values, max_idx + 1);
    }
    flip(values, curr_size);
  }
}
