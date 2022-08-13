#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/utils.hh"

bool is_perm_of(const std::string& str1, const std::string& str2) {
  std::vector<std::function<bool(const std::string&, const std::string&)>> implementations{
      // implementation
      [](const std::string& str1, const std::string& str2) {
        if (str1.size() != str2.size()) {
          return false;
        }

        std::unordered_map<char, size_t> map1, map2;
        auto mapper = [](auto& map) { return [&map](char c) { ++map[c]; }; };
        for_each(str1.begin(), str1.end(), mapper(map1));
        for_each(str2.begin(), str2.end(), mapper(map2));

        return map1.end() == find_if(map1.begin(), map1.end(), [&map2](auto e) { return map2[e.first] != e.second; });
      },

      // implementation
      [](const std::string& str1, const std::string& str2) {
        if (str1.size() != str2.size()) {
          return false;
        }
        std::string s1{str1}, s2{str2};
        std::sort(s1.begin(), s1.end());
        std::sort(s2.begin(), s2.end());
        return s1 == s2;
      },
  };

  return call_implementations(implementations, str1, str2);
}
