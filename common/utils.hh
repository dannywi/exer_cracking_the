#pragma once
#include <optional>
#include <vector>

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

template <typename RES, typename IMPL, typename... ARGS>
std::vector<RES> call_implementations(IMPL implementations, ARGS... args) {
  std::vector<RES> results;
  for (auto impl : implementations) {
    results.emplace_back(impl(args...));
  }

  // all results should be the same
  RES* last = nullptr;
  for (auto curr : results) {
    if(last && last != curr) {
      throw std::logic_error("different results");
    }
    last = &curr;
  }
  return results;
}