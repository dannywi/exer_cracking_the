#pragma once

#include <unordered_set>
#include <vector>

#include "common/utils.hh"
#include "linked_list.hh"

// using cache, n time, n space
template <typename T>
void ll_rm_dup1(typename linked_list<T>::ptr_t node) {
  typename linked_list<T>::ptr_t last{nullptr};
  std::unordered_set<T> cache;
  while (node) {
    if (cache.find(node->val) != cache.end()) {
      // duplicate, remove (last can't be null)
      last->next = node->next;
    } else {
      cache.emplace(node->val);
      last = node;
    }
    node = node->next;
  }
}

// not using cache, n^2 time, constant space
template <typename T>
void ll_rm_dup2(typename linked_list<T>::ptr_t node) {
  typename linked_list<T>::ptr_t root{node};
  auto rm_fn = [](typename linked_list<T>::ptr_t p) {
    T val = p->val;
    typename linked_list<T>::ptr_t last{p};
    p = p->next;
    while (p) {
      if (p->val == val) {
        last->next = p->next;
      } else {
        last = p;
      }
      p = p->next;
    }
  };

  while (node) {
    rm_fn(node);
    node = node->next;
  }
}