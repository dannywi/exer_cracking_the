#pragma once

#include <vector>

// implement queue using stacks
template <typename T>
class queue_with_stacks {
  class stack {
    std::vector<T> vals_;
    void throw_on_empty() const {
      if (vals_.empty()) {
        throw std::logic_error("empty");
      }
    }

   public:
    void push(T v) { vals_.push_back(v); }

    T peek() const {
      throw_on_empty();
      return vals_.back();
    }

    void pop() {
      throw_on_empty();
      vals_.pop_back();
    }

    bool empty() const { return vals_.empty(); }
  };

  stack in_list;
  stack out_list;

  void shift_to_out() {
    // this is an optimization, instead shifting everything to in_list before push
    // and out_list before pop everytime, don't shift on push and only shift on pop
    // when out_list is empty
    if (out_list.empty()) {
      while (!in_list.empty()) {
        T v = in_list.peek();
        in_list.pop();
        out_list.push(v);
      }
    }
  }

 public:
  void push(T v) {
    // notice with the optimization we don't need to shift here
    // just keep stacking new pushes to in_list
    in_list.push(v);
  }

  T peek() {
    shift_to_out();
    return out_list.peek();
  }

  void pop() {
    shift_to_out();
    out_list.pop();
  }

  bool empty() const { return out_list.empty() && in_list.empty(); }
};