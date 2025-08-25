#include <vector>
#include <cstddef>
#include <algorithm>

namespace {

std::size_t min_run_length(std::size_t n) {
  std::size_t r = 0;
  while (n >= 64) {
    r |= n & 1u;
    n >>= 1u;
  }
  return n + r;
}

void insertion_sort_range(std::vector<int>& values,
                          std::size_t left,
                          std::size_t right) {
  for (std::size_t i = left + 1; i <= right; ++i) {
    const int key = values[i];
    std::size_t j = i;
    while (j > left && values[j - 1] > key) {
      values[j] = values[j - 1];
      --j;
    }
    values[j] = key;
  }
}

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

}  // namespace

void tim_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  const std::size_t min_run = min_run_length(n);
  for (std::size_t start = 0; start < n; start += min_run) {
    const std::size_t end = std::min(start + min_run - 1, n - 1);
    insertion_sort_range(values, start, end);
  }

  std::vector<int> buffer(n);
  for (std::size_t size = min_run; size < n; size *= 2) {
    for (std::size_t left = 0; left < n; left += 2 * size) {
      const std::size_t mid = left + size - 1;
      if (mid >= n - 1) {
        continue;
      }
      const std::size_t right = std::min(left + 2 * size - 1, n - 1);
      merge_ranges(values, buffer, left, mid, right);
    }
  }
}
