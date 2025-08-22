#include <vector>
#include <cstddef>
#include <utility>

void gnome_sort(std::vector<int>& values) {
  const std::size_t n = values.size();
  if (n < 2) {
    return;
  }

  std::size_t index = 0;
  while (index < n) {
    if (index == 0 || values[index] >= values[index - 1]) {
      ++index;
    } else {
      std::swap(values[index], values[index - 1]);
      --index;
    }
  }
}
