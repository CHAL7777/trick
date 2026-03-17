#include <vector>
#include <cstddef>

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

}  // namespace

void merge_sort(std::vector<int>& values) {
  if (values.size() < 2) {
    return;
  }
  std::vector<int> buffer(values.size());
  merge_sort_range(values, buffer, 0, values.size() - 1);
}
