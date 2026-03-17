#include <vector>
#include <cstddef>
#include <utility>

void bubble_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  bool swapped = true;
  for (std::size_t i = 0; i + 1 < n && swapped; ++i) {
    swapped = false;
    for (std::size_t j = 0; j + 1 < n - i; ++j) {
      if (values[j] > values[j + 1]) {
        std::swap(values[j], values[j + 1]);
        swapped = true;
      }
    }
  }
}
