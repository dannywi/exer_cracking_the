#pragma once

#include "linked_list.hh"

// assume 1st means last non-null
// 0th throws, empty list throws, k more than nodes throws

// simply check size first, n time, constant space
template <typename T>
T kth_last1(typename linked_list<T>::ptr_t node, size_t k) {
  if (k == 0) {
    throw std::logic_error("invalid k");
  }

  if (!node) {
    throw std::logic_error("empty list");
  }

  // get size
  typename linked_list<T>::ptr_t p{node};
  size_t sz = 0;
  while (p) {
    ++sz;
    p = p->next;
  }

  if (k > sz) {
    throw std::logic_error("k more than nodes");
  }

  p = node;
  size_t cnt = sz - k;
  while (cnt-- >= 1) {
    p = p->next;
  }
  return p->val;
}

// use 2 iterators, n time, constant space
template <typename T>
T kth_last2(typename linked_list<T>::ptr_t node, size_t k) {
  if (k == 0) {
    throw std::logic_error("invalid k");
  }

  if (!node) {
    throw std::logic_error("empty list");
  }

  // get size
  typename linked_list<T>::ptr_t b{node};
  while (k-- > 0) {
    b = b->next;
    if (!b && k > 0) {
      throw std::logic_error("k more than nodes");
    }
  }

  while (b) {
    node = node->next;
    b = b->next;
  }

  return node->val;
}