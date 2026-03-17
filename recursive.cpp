#include <vector>
#include <cstddef>
#include <utility>

namespace {

void merge_ranges(std::vector<int>& values,
                  std::vector<int>& buffer,
                  std::size_t left,
                  std::size_t mid,
                  std::size_t right) {
  std::size_t i = left;
  std::size_t j = mid + 1;
  std::size_t k = left;

  while (i <= mid && j <= right) {
    if (values[i] <= values[j]) {
      buffer[k++] = values[i++];
    } else {
      buffer[k++] = values[j++];
    }
  }

  while (i <= mid) {
    buffer[k++] = values[i++];
  }

  while (j <= right) {
    buffer[k++] = values[j++];
  }

  for (std::size_t idx = left; idx <= right; ++idx) {
    values[idx] = buffer[idx];
  }
}

void merge_sort_range(std::vector<int>& values,
                      std::vector<int>& buffer,
                      std::size_t left,
                      std::size_t right) {
  if (left >= right) {
    return;
  }

  const std::size_t mid = left + (right - left) / 2;
  merge_sort_range(values, buffer, left, mid);
  merge_sort_range(values, buffer, mid + 1, right);
  merge_ranges(values, buffer, left, mid, right);
}

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

void merge_sort(std::vector<int>& values) {
  if (values.size() < 2) {
    return;
  }
  std::vector<int> buffer(values.size());
  merge_sort_range(values, buffer, 0, values.size() - 1);
}

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
