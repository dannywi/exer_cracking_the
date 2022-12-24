#include <gtest/gtest.h>

#include <cstdlib>
#include <ctime>

#include "queue_with_stacks.hh"

TEST(queue_with_stacks, BasicAssertions) {
  queue_with_stacks<int> queue;
  EXPECT_EQ(queue.empty(), true);
  queue.push(1);
  EXPECT_EQ(queue.empty(), false);
  queue.push(2);
  queue.push(3);
  queue.push(4);
  queue.push(5);
  EXPECT_EQ(queue.peek(), 1);
  queue.pop();
  queue.pop();
  EXPECT_EQ(queue.peek(), 3);
  queue.push(6);
  EXPECT_EQ(queue.peek(), 3);
  queue.pop();
  EXPECT_EQ(queue.peek(), 4);
  queue.pop();
  queue.pop();
  EXPECT_EQ(queue.peek(), 6);
  queue.pop();
  EXPECT_EQ(queue.empty(), true);
  EXPECT_THROW(queue.peek(), std::logic_error);
  EXPECT_THROW(queue.pop(), std::logic_error);

  auto check_sorted = [](auto cont, auto comp) -> bool {
    while (!cont.empty()) {
      auto v = cont.peek();
      cont.pop();
      if (cont.empty()) break;
      if (!comp(v, cont.peek())) return false;
    }
    return true;
  };

  std::srand(std::time(nullptr));
  for (size_t i = 0; i < 10; ++i) queue.push(std::rand() % 50 - 25);

  auto comp = [](auto a, auto b) -> bool { return a < b; };
  util::sort_with_stacks(queue, comp);
  EXPECT_TRUE(check_sorted(queue, comp));
  util::flush_queue(queue);
}
