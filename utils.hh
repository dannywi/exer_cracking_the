#pragma once
#include <optional>

template <typename I, typename... ARGS>
bool call_implementations(I implementations, ARGS... args) {
  std::optional<bool> ret;

  for (auto impl : implementations) {
    bool cur = impl(args...);
    if (ret.has_value()) {
      if (ret != cur) {
        throw std::logic_error("different results");
      }
    } else {
      ret = cur;
    }
  }

  return ret.value();
}