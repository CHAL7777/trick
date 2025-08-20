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

void quick_sort_range(std::vector<int>& values,
                      std::size_t left,
                      std::size_t right) {
  const std::size_t kInsertionLimit = 16;
  while (left < right) {
    if (right - left + 1 <= kInsertionLimit) {
      insertion_sort_range(values, left, right);
      return;
    }

    const std::size_t pivot = partition_range(values, left, right);
    if (pivot - left < right - (pivot + 1)) {
      quick_sort_range(values, left, pivot);
      left = pivot + 1;
    } else {
      quick_sort_range(values, pivot + 1, right);
      right = pivot;
    }
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

void quick_sort(std::vector<int>& values) {
  if (values.size() < 2) {
    return;
  }
  quick_sort_range(values, 0, values.size() - 1);
}
