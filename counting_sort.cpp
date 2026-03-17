#include <vector>
#include <cstddef>

void counting_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  int min_val = values[0];
  int max_val = values[0];
  for (int value : values) {
    if (value < min_val) {
      min_val = value;
    }
    if (value > max_val) {
      max_val = value;
    }
  }

  const std::size_t range = static_cast<std::size_t>(max_val - min_val) + 1;
  std::vector<std::size_t> counts(range, 0);
  for (int value : values) {
    ++counts[static_cast<std::size_t>(value - min_val)];
  }

  std::size_t idx = 0;
  for (std::size_t i = 0; i < range; ++i) {
    while (counts[i] > 0) {
      values[idx++] = static_cast<int>(i) + min_val;
      --counts[i];
    }
  }
}
