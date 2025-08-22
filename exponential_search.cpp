#include <vector>
#include <cstddef>
#include <algorithm>

int exponential_search(const std::vector<int>& values, int target) {
  const std::size_t n = values.size();
  if (n == 0) {
    return -1;
  }

  if (values[0] == target) {
    return 0;
  }

  std::size_t bound = 1;
  while (bound < n && values[bound] < target) {
    bound *= 2;
  }

  std::size_t left = bound / 2;
  std::size_t right = std::min(bound, n - 1);

  while (left <= right) {
    const std::size_t mid = left + (right - left) / 2;
    if (values[mid] == target) {
      return static_cast<int>(mid);
    }
    if (values[mid] < target) {
      left = mid + 1;
    } else {
      if (mid == 0) {
        break;
      }
      right = mid - 1;
    }
  }

  return -1;
}
