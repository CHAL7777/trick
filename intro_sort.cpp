#include <vector>
#include <cstddef>
#include <algorithm>
#include <cmath>
#include <utility>

namespace {

std::size_t median_of_three(const std::vector<int>& values,
                            std::size_t a,
                            std::size_t b,
                            std::size_t c) {
  if (values[a] < values[b]) {
    if (values[b] < values[c]) {
      return b;
    }
    if (values[a] < values[c]) {
      return c;
    }
    return a;
  }
  if (values[a] < values[c]) {
    return a;
  }
  if (values[b] < values[c]) {
    return c;
  }
  return b;
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

std::size_t partition_range(std::vector<int>& values,
                            std::size_t left,
                            std::size_t right) {
  const std::size_t mid = left + (right - left) / 2;
  const std::size_t pivot_index = median_of_three(values, left, mid, right);
  const int pivot = values[pivot_index];

  std::ptrdiff_t i = static_cast<std::ptrdiff_t>(left) - 1;
  std::ptrdiff_t j = static_cast<std::ptrdiff_t>(right) + 1;
  while (true) {
    do {
      ++i;
    } while (values[static_cast<std::size_t>(i)] < pivot);

    do {
      --j;
    } while (values[static_cast<std::size_t>(j)] > pivot);

    if (i >= j) {
      return static_cast<std::size_t>(j);
    }
    std::swap(values[static_cast<std::size_t>(i)],
              values[static_cast<std::size_t>(j)]);
  }
}

void heap_sort_range(std::vector<int>& values,
                     std::size_t left,
                     std::size_t right) {
  auto begin = values.begin() + static_cast<std::ptrdiff_t>(left);
  auto end = values.begin() + static_cast<std::ptrdiff_t>(right + 1);
  std::make_heap(begin, end);
  std::sort_heap(begin, end);
}

void intro_sort_range(std::vector<int>& values,
                      std::size_t left,
                      std::size_t right,
                      int depth_limit) {
  const std::size_t kInsertionLimit = 16;
  while (left < right) {
    const std::size_t length = right - left + 1;
    if (length <= kInsertionLimit) {
      insertion_sort_range(values, left, right);
      return;
    }

    if (depth_limit == 0) {
      heap_sort_range(values, left, right);
      return;
    }

    --depth_limit;
    const std::size_t pivot = partition_range(values, left, right);
    if (pivot - left < right - (pivot + 1)) {
      intro_sort_range(values, left, pivot, depth_limit);
      left = pivot + 1;
    } else {
      intro_sort_range(values, pivot + 1, right, depth_limit);
      right = pivot;
    }
  }
}

}  // namespace

void intro_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  const int depth_limit = static_cast<int>(2 * std::floor(std::log2(static_cast<double>(n))));
  intro_sort_range(values, 0, n - 1, depth_limit);
}
