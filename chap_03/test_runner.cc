#include <gtest/gtest.h>

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
}