#include <vector>
#include <cstddef>
#include <utility>

void cycle_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  for (std::size_t cycle_start = 0; cycle_start + 1 < n; ++cycle_start) {
    int item = values[cycle_start];
    std::size_t pos = cycle_start;

    for (std::size_t i = cycle_start + 1; i < n; ++i) {
      if (values[i] < item) {
        ++pos;
      }
    }

    if (pos == cycle_start) {
      continue;
    }

    while (pos < n && values[pos] == item) {
      ++pos;
    }
    if (pos >= n) {
      continue;
    }

    std::swap(item, values[pos]);

    while (pos != cycle_start) {
      pos = cycle_start;
      for (std::size_t i = cycle_start + 1; i < n; ++i) {
        if (values[i] < item) {
          ++pos;
        }
      }

      while (pos < n && values[pos] == item) {
        ++pos;
      }
      if (pos >= n) {
        break;
      }

      std::swap(item, values[pos]);
    }
  }
}
