#include "test.h"

TEST(stack, standart_constructor) {
    s21::stack<int> stack_int;
    // std::stack<int> true_stack;
    EXPECT_EQ(0u, stack_int.size());
}

TEST(stack, parametric_constructor) {
    s21::stack<int> stack_int(3);
    EXPECT_EQ(3u, stack_int.size());
    EXPECT_EQ(0, stack_int.top());
}

TEST(stack, push) {
    s21::stack<int> stack_int;
    EXPECT_EQ(0u, stack_int.size());
    stack_int.push(1);
    EXPECT_EQ(1u, stack_int.size());
    EXPECT_EQ(1, stack_int.top());
}
