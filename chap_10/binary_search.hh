#pragma once

namespace cr {
template <typename T, typename It>
bool binary_search(It bg, It en, T val) {
  It md = (en - bg) / 2;
  if (val < *md) {
    return binary_search(bg, md, val);
  } else if (val > *md) {
    return binary_search(md + 1, en, val);
  }
  return true;
}
}  // namespace cr
