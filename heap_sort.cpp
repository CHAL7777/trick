#include <vector>
#include <cstddef>
#include <utility>

namespace {

void sift_down(std::vector<int>& values, std::size_t start, std::size_t end) {
  std::size_t root = start;
  while (true) {
    std::size_t child = root * 2 + 1;
    if (child > end) {
      break;
    }
    std::size_t swap_idx = root;
    if (values[swap_idx] < values[child]) {
      swap_idx = child;
    }
    if (child + 1 <= end && values[swap_idx] < values[child + 1]) {
      swap_idx = child + 1;
    }
    if (swap_idx == root) {
      return;
    }
    std::swap(values[root], values[swap_idx]);
    root = swap_idx;
  }
}

}  // namespace

void heap_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  for (std::size_t start = n / 2; start-- > 0;) {
    sift_down(values, start, n - 1);
  }

  for (std::size_t end = n - 1; end > 0; --end) {
    std::swap(values[0], values[end]);
    sift_down(values, 0, end - 1);
  }
}
