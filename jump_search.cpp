#include <vector>
#include <cstddef>
#include <cmath>
#include <algorithm>

int jump_search(const std::vector<int>& values, int target) {
  const std::size_t n = values.size();
  if (n == 0) {
    return -1;
  }

  std::size_t step = static_cast<std::size_t>(std::sqrt(static_cast<double>(n)));
  if (step == 0) {
    step = 1;
  }

  std::size_t prev = 0;
  std::size_t curr = step;

  while (prev < n && values[std::min(curr, n) - 1] < target) {
    prev = curr;
    curr += step;
    if (prev >= n) {
      return -1;
    }
  }

  const std::size_t end = std::min(curr, n);
  for (std::size_t i = prev; i < end; ++i) {
    if (values[i] == target) {
      return static_cast<int>(i);
    }
  }

  return -1;
}
