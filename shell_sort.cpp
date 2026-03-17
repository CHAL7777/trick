#include <vector>
#include <cstddef>

void shell_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  for (std::size_t gap = n / 2; gap > 0; gap /= 2) {
    for (std::size_t i = gap; i < n; ++i) {
      const int temp = values[i];
      std::size_t j = i;
      while (j >= gap && values[j - gap] > temp) {
        values[j] = values[j - gap];
        j -= gap;
      }
      values[j] = temp;
    }
  }
}
