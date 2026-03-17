#include <vector>
#include <cstddef>

int binary_search(const std::vector<int>& values, int target) {
  if (values.empty()) {
    return -1;
  }

  std::size_t left = 0;
  std::size_t right = values.size() - 1;

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
