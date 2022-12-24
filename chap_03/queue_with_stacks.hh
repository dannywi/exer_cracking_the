#pragma once

#include <iostream>
#include <vector>

// rudimentary stack
template <typename T>
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

// implement queue using stacks
template <typename T>
class queue_with_stacks {
  stack<T> in_list;
  stack<T> out_list;

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
  typedef T value_type;

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

namespace util {
template <typename T>
void sort_with_stacks(queue_with_stacks<T>& queue, std::function<bool(T, T)> comp) {
  stack<T> tgt, keep;
  while (!queue.empty()) {
    // 1. pop from queue
    T v = queue.peek();
    queue.pop();

    // 2. while tgt not empty and comp tgt top not true, move to keep
    while (!tgt.empty() && !comp(v, tgt.peek())) {
      T t = tgt.peek();
      tgt.pop();
      keep.push(t);
    }

    // 3. insert val
    tgt.push(v);

    // 4. move back keep to tgt
    while (!keep.empty()) {
      T k = keep.peek();
      keep.pop();
      tgt.push(k);
    }
  }

  // 5. insert tgt to queue
  while (!tgt.empty()) {
    T v = tgt.peek();
    tgt.pop();
    queue.push(v);
  }
}

template <typename T>
void flush_queue(queue_with_stacks<T>& q) {
  std::cout << "[ ";
  while (!q.empty()) {
    std::cout << q.peek() << " ";
    q.pop();
  }
  std::cout << "]" << std::endl;
}
}  // namespace util
