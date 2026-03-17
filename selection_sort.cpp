#include <vector>
#include <cstddef>
#include <utility>

void selection_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  for (std::size_t i = 0; i < n - 1; ++i) {
    std::size_t min_idx = i;
    for (std::size_t j = i + 1; j < n; ++j) {
      if (values[j] < values[min_idx]) {
        min_idx = j;
      }
    }
    if (min_idx != i) {
      std::swap(values[i], values[min_idx]);
    }
  }
}
