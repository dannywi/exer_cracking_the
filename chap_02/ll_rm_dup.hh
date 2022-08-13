#pragma once

#include <unordered_set>
#include <vector>

#include "common/utils.hh"
#include "linked_list.hh"

template <typename T>
void ll_rm_dup1(std::shared_ptr<linked_list<T>> root) {
  std::shared_ptr<linked_list<T>> curr = root;
  std::shared_ptr<linked_list<T>> last{nullptr};
  std::unordered_set<T> cache;
  while (curr) {
    if (cache.find(curr->val) != cache.end()) {
      // duplicate, remove (last can't be null)
      last->next = curr->next;
      curr = last->next;
    } else {
      cache.emplace(curr->val);
      last = curr;
      curr = curr->next;
    }
  }
}