#pragma once

#include <bitset>
#include <functional>
#include <string>
#include <unordered_set>
#include <vector>

#include "common/utils.hh"

bool is_char_unique(const std::string& str) {
  std::vector<std::function<bool(const std::string&)>> implementations{
      // implementation
      [](const std::string& str) {
        std::unordered_set<char> set;
        for (char c : str) {
          if (set.find(c) != set.end()) {
            return false;
          }
          set.emplace(c);
        }
        return true;
      },

      // implementation
      [](const std::string& str) {
        std::bitset<sizeof(char)> set;
        for (char c : str) {
          if (set[c]) {
            return false;
          }
          set[c] = 1;
        }
        return true;
      },

      // implementation, n^2 complexity, but no extra space
      [](const std::string& str) {
        size_t num = str.size();
        for (size_t c = 0; c < num; ++c) {
          for (size_t i = c + 1; i < num; ++i) {
            if (str[c] == str[i]) {
              return false;
            }
          }
        }
        return true;
      },
  };

  return call_implementations(implementations, str);
}
