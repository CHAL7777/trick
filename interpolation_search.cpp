#include <vector>
#include <cstddef>

int interpolation_search(const std::vector<int>& values, int target) {
  if (values.empty()) {
    return -1;
  }

  std::size_t low = 0;
  std::size_t high = values.size() - 1;

  while (low <= high && target >= values[low] && target <= values[high]) {
    const long long low_val = values[low];
    const long long high_val = values[high];

    if (high_val == low_val) {
      if (values[low] == target) {
        return static_cast<int>(low);
      }
      break;
    }

    const double fraction = static_cast<double>(target - low_val)
        / static_cast<double>(high_val - low_val);
    std::size_t pos = low + static_cast<std::size_t>((high - low) * fraction);
    if (pos < low) {
      pos = low;
    } else if (pos > high) {
      pos = high;
    }

    if (values[pos] == target) {
      return static_cast<int>(pos);
    }
    if (values[pos] < target) {
      low = pos + 1;
    } else {
      if (pos == 0) {
        break;
      }
      high = pos - 1;
    }
  }

  return -1;
}
