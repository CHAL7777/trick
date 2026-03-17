#include <vector>
#include <cstddef>

int linear_search(const std::vector<int>& values, int target) {
  for (std::size_t i = 0; i < values.size(); ++i) {
    if (values[i] == target) {
      return static_cast<int>(i);
    }
  }
  return -1;
}
