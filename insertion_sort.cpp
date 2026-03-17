#include <vector>
#include <cstddef>

void insertion_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  for (std::size_t i = 1; i < n; ++i) {
    const int key = values[i];
    std::size_t j = i;
    while (j > 0 && values[j - 1] > key) {
      values[j] = values[j - 1];
      --j;
    }
    values[j] = key;
  }
}
