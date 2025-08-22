#include <vector>
#include <cstddef>
#include <utility>

void odd_even_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  bool sorted = false;
  while (!sorted) {
    sorted = true;

    for (std::size_t i = 1; i + 1 < n; i += 2) {
      if (values[i] > values[i + 1]) {
        std::swap(values[i], values[i + 1]);
        sorted = false;
      }
    }

    for (std::size_t i = 0; i + 1 < n; i += 2) {
      if (values[i] > values[i + 1]) {
        std::swap(values[i], values[i + 1]);
        sorted = false;
      }
    }
  }
}
