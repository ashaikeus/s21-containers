#include <stack>

#include "test.h"

TEST(stack, standart_constructor) {
  s21::stack<int> stack_int;
  std::stack<int> true_stack;
  EXPECT_EQ(true_stack.size(), stack_int.size());

  s21::stack<char> stack_char;
  std::stack<char> true_stack_char;
  EXPECT_EQ(true_stack_char.size(), stack_char.size());
}

TEST(stack, list_constructor) {
  s21::stack<int> stack_int = {0, 0, 0, 0};
  std::stack<int> true_stack;
  true_stack.push(0);
  true_stack.push(0);
  true_stack.push(0);
  true_stack.push(0);
  EXPECT_EQ(true_stack.size(), stack_int.size());
  EXPECT_EQ(true_stack.top(), stack_int.top());
  stack_int.push(1);
  true_stack.push(1);
  EXPECT_EQ(true_stack.size(), stack_int.size());
  EXPECT_EQ(true_stack.top(), stack_int.top());
}

TEST(stack, list_constructor_empty) {
  s21::stack<int> stack_int = {};
  std::stack<int> true_stack = {};
  EXPECT_EQ(true_stack.size(), stack_int.size());
  stack_int.push(1);
  true_stack.push(1);
  EXPECT_EQ(true_stack.size(), stack_int.size());
  EXPECT_EQ(true_stack.top(), stack_int.top());
}

TEST(stack, copy_constructor) {
  s21::stack<int> stack;
  s21::stack<int> copy_stack(stack);
  EXPECT_EQ(stack.size(), copy_stack.size());

  s21::stack<int> stack_five_elements = {0, 1, 2, 3, 4};
  s21::stack<int> copy_stack_five_elements(stack_five_elements);
  EXPECT_EQ(stack_five_elements.size(), copy_stack_five_elements.size());
  EXPECT_EQ(stack_five_elements.top(), copy_stack_five_elements.top());
}

TEST(stack, move_constructor) {
  s21::stack<int> stack_five_elements = {0, 1, 2, 3, 4};
  s21::stack<int> move_stack_five_elements(std::move(stack_five_elements));

  EXPECT_EQ(0u, stack_five_elements.size());

  EXPECT_EQ(5u, move_stack_five_elements.size());
  EXPECT_EQ(4, move_stack_five_elements.top());
}

TEST(stack, top_size) {
  s21::stack<int> stack_int = {1};
  std::stack<int> true_stack;
  true_stack.push(1);
  EXPECT_EQ(true_stack.size(), stack_int.size());
  EXPECT_EQ(true_stack.top(), stack_int.top());
}

TEST(stack, empty_push_pop) {
  s21::stack<int> stack_int;
  std::stack<int> true_stack;
  EXPECT_EQ(stack_int.empty(), true_stack.empty());
  true_stack.push(1);
  stack_int.push(1);
  EXPECT_EQ(true_stack.size(), stack_int.size());
  EXPECT_EQ(true_stack.top(), stack_int.top());
  EXPECT_EQ(stack_int.empty(), true_stack.empty());
  true_stack.pop();
  stack_int.pop();
  EXPECT_EQ(true_stack.size(), stack_int.size());
  EXPECT_EQ(stack_int.empty(), true_stack.empty());
}

TEST(stack, swap) {
  s21::stack<int> stack1 = {0, 1, 2};
  s21::stack<int> stack2 = {3, 4};
  EXPECT_EQ(2, stack1.top());
  EXPECT_EQ(4, stack2.top());
  EXPECT_EQ(3u, stack1.size());
  EXPECT_EQ(2u, stack2.size());
  stack1.swap(stack2);
  EXPECT_EQ(2u, stack1.size());
  EXPECT_EQ(3u, stack2.size());
  EXPECT_EQ(4, stack1.top());
  EXPECT_EQ(2, stack2.top());
}

TEST(stack, insert_many_front) {
  s21::stack<int> stack1 = {0, 1, 2};
  s21::stack<int> stack2 = {3, 4};
  stack2.insert_many_front(stack1, stack1);
  EXPECT_EQ(8u, stack2.size());
}
