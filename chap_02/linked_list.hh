#pragma once

#include <memory>
#include <vector>

template <typename T>
struct linked_list {
  using ptr_t = std::shared_ptr<linked_list<T>>;
  T val;
  ptr_t next{nullptr};

  static void print(ptr_t p) {
    std::cout << "[";
    bool first = true;
    while (p) {
      if (!first) {
        std::cout << " ";
      }
      first = false;
      std::cout << p->val;
      p = p->next;
    };
    std::cout << "]" << std::endl;
  };

  static ptr_t from_vector(const std::vector<T>& vals) {
    if (vals.empty()) {
      return nullptr;
    }
    ptr_t curr = std::make_shared<linked_list<T>>();
    ptr_t root = curr;
    bool first = true;
    for (auto v : vals) {
      if (!first) {
        curr->next = std::make_shared<linked_list<T>>();
        curr = curr->next;
      }
      first = false;
      curr->val = v;
    }
    return root;
  }

  static std::vector<T> to_vector(ptr_t p) {
    std::vector<T> res;
    while (p) {
      res.emplace_back(p->val);
      p = p->next;
    }
    return res;
  }
};