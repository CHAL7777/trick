#include <vector>
#include <cstddef>

int ternary_search(const std::vector<int>& values, int target) {
  if (values.empty()) {
    return -1;
  }

  std::ptrdiff_t left = 0;
  std::ptrdiff_t right = static_cast<std::ptrdiff_t>(values.size() - 1);

  while (left <= right) {
    const std::ptrdiff_t third = (right - left) / 3;
    const std::ptrdiff_t mid1 = left + third;
    const std::ptrdiff_t mid2 = right - third;

    const int val1 = values[static_cast<std::size_t>(mid1)];
    const int val2 = values[static_cast<std::size_t>(mid2)];

    if (val1 == target) {
      return static_cast<int>(mid1);
    }
    if (val2 == target) {
      return static_cast<int>(mid2);
    }

    if (target < val1) {
      right = mid1 - 1;
    } else if (target > val2) {
      left = mid2 + 1;
    } else {
      left = mid1 + 1;
      right = mid2 - 1;
    }
  }

  return -1;
}
