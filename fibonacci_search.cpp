#include <vector>
#include <cstddef>
#include <algorithm>

int fibonacci_search(const std::vector<int>& values, int target) {
  const std::size_t n = values.size();
  if (n == 0) {
    return -1;
  }

  std::size_t fib_mm2 = 0;
  std::size_t fib_mm1 = 1;
  std::size_t fib_m = fib_mm2 + fib_mm1;

  while (fib_m < n) {
    fib_mm2 = fib_mm1;
    fib_mm1 = fib_m;
    fib_m = fib_mm2 + fib_mm1;
  }

  std::ptrdiff_t offset = -1;

  while (fib_m > 1) {
    const std::ptrdiff_t i = std::min(
        offset + static_cast<std::ptrdiff_t>(fib_mm2),
        static_cast<std::ptrdiff_t>(n - 1));

    const int value = values[static_cast<std::size_t>(i)];
    if (value < target) {
      fib_m = fib_mm1;
      fib_mm1 = fib_mm2;
      fib_mm2 = fib_m - fib_mm1;
      offset = i;
    } else if (value > target) {
      fib_m = fib_mm2;
      fib_mm1 = fib_mm1 - fib_mm2;
      fib_mm2 = fib_m - fib_mm1;
    } else {
      return static_cast<int>(i);
    }
  }

  if (fib_mm1 && offset + 1 < static_cast<std::ptrdiff_t>(n)
      && values[static_cast<std::size_t>(offset + 1)] == target) {
    return static_cast<int>(offset + 1);
  }

  return -1;
}
