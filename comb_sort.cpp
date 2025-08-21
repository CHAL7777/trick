#include <vector>
#include <cstddef>
#include <utility>

void comb_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  std::size_t gap = n;
  bool swapped = true;
  while (gap > 1 || swapped) {
    gap = (gap * 10) / 13;
    if (gap < 1) {
      gap = 1;
    }

    swapped = false;
    for (std::size_t i = 0; i + gap < n; ++i) {
      if (values[i] > values[i + gap]) {
        std::swap(values[i], values[i + gap]);
        swapped = true;
      }
    }
  }
}
