#include <vector>
#include <cstddef>
#include <algorithm>
#include <cmath>

void bucket_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  int min_val = values[0];
  int max_val = values[0];
  for (int value : values) {
    if (value < min_val) {
      min_val = value;
    }
    if (value > max_val) {
      max_val = value;
    }
  }

  const int range_int = max_val - min_val;
  if (range_int == 0) {
    return;
  }

  std::size_t bucket_count = static_cast<std::size_t>(std::sqrt(static_cast<double>(n)));
  if (bucket_count < 1) {
    bucket_count = 1;
  }

  std::vector<std::vector<int>> buckets(bucket_count);
  for (int value : values) {
    const std::size_t index = static_cast<std::size_t>(
        (static_cast<long long>(value - min_val) * bucket_count)
        / (static_cast<long long>(range_int) + 1));
    buckets[index].push_back(value);
  }

  std::size_t out = 0;
  for (auto& bucket : buckets) {
    std::sort(bucket.begin(), bucket.end());
    for (int value : bucket) {
      values[out++] = value;
    }
  }
}
