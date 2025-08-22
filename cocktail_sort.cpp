#include <vector>
#include <cstddef>
#include <utility>

void cocktail_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  std::size_t start = 0;
  std::size_t end = n - 1;
  bool swapped = true;

  while (swapped) {
    swapped = false;
    for (std::size_t i = start; i < end; ++i) {
      if (values[i] > values[i + 1]) {
        std::swap(values[i], values[i + 1]);
        swapped = true;
      }
    }

    if (!swapped) {
      break;
    }

    swapped = false;
    if (end == 0) {
      break;
    }
    --end;

    for (std::size_t i = end; i > start; --i) {
      if (values[i - 1] > values[i]) {
        std::swap(values[i - 1], values[i]);
        swapped = true;
      }
    }
    ++start;
  }
}
