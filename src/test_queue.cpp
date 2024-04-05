#include <queue>

#include "s21_containers.h"
// #include "s21_containersplus.h"
#include "test.h"

using namespace std;

// template <typename value_type1, typename value_type2>
// bool equal_queue(s21::queue<value_type1> my_queue,
//                  std::queue<value_type2> std_queue) {
//   bool res = (my_queue.size() == std_queue.size());
//   while (!my_queue.empty() && !std_queue.empty()) {
//     if (my_queue.front() != std_queue.front()) res = false;
//     my_queue.pop();
//     std_queue.pop();
//   }
//   return res;
// }

template <typename value_type>
bool equal_queue(s21::queue<value_type> my_queue,
                 std::queue<value_type> true_queue) {
  bool result = true;
  if (my_queue.size() == true_queue.size()) {
    while (!my_queue.empty() && !true_queue.empty()) {
      if (my_queue.front() != true_queue.front()) {
        result = false;
      }
      my_queue.pop();
      true_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(queue, standart_constructor) {
  s21::queue<int> my_queue;
  std::queue<int> true_queue_int;

  ASSERT_TRUE(my_queue.empty());
  ASSERT_EQ(my_queue.size(), 0u);

  my_queue = {1, 2, 3, 7, 9};
  std::initializer_list<int> il = {1, 2, 3, 7, 9};
  std::queue<int> true_queue_int2{il};
  ASSERT_TRUE(equal_queue(my_queue, true_queue_int2));
}

TEST(queue, initializer_list_constructor) {
  s21::queue<int> my_queue{1, 2, 3, 4};
  std::queue<int> true_queue;
  for (int i = 1; i < 5; ++i) true_queue.push(i);
  EXPECT_EQ(my_queue.front(), true_queue.front());
  EXPECT_EQ(my_queue.back(), true_queue.back());
  ASSERT_TRUE(equal_queue(my_queue, true_queue));
}

TEST(queue, copy_move_constructor) {
  s21::queue<int> my_queue{1, 2, 3, 4};
  std::queue<int> true_queue;
  for (int i = 1; i < 5; ++i) true_queue.push(i);
  s21::queue<int> my_queue2 = my_queue;
  ASSERT_TRUE(equal_queue(my_queue2, true_queue));
  my_queue = std::move(my_queue2);
  ASSERT_TRUE(equal_queue(my_queue, true_queue));
}

TEST(queue, front_back_reference) {
  s21::queue<int> my_queue;
  ASSERT_ANY_THROW(my_queue.front());
  ASSERT_ANY_THROW(my_queue.back());
  std::queue<int> true_queue;
  for (int i = 1; i < 5; ++i) {
    true_queue.push(i);
    my_queue.push(i);
  }
  EXPECT_EQ(my_queue.front(), true_queue.front());
  EXPECT_EQ(my_queue.back(), true_queue.back());
}

TEST(queue, empty_bool) {
  s21::queue<int> my_queue;
  std::queue<int> true_queue;
  EXPECT_EQ(my_queue.empty(), true_queue.empty());
  true_queue.push(2);
  my_queue.push(2);
  EXPECT_EQ(my_queue.empty(), true_queue.empty());
}

TEST(queue, Size) {
  s21::queue<int> my_queue{1, 2, 3, 4, 5, 6};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6};
  std::queue<int> true_queue{il};
  EXPECT_EQ(my_queue.size(), true_queue.size());
}

TEST(queue, Push) {
  s21::queue<int> my_queue;
  std::queue<int> true_queue;
  my_queue.push(0);
  true_queue.push(0);
  my_queue.push(3);
  true_queue.push(3);
  EXPECT_TRUE(equal_queue(my_queue, true_queue));
}

TEST(queue, Pop) {
  s21::queue<int> my_queue{1, 2, 3, 4, 5, 6};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6};
  std::queue<int> true_queue{il};
  my_queue.pop();
  my_queue.pop();
  true_queue.pop();
  true_queue.pop();
  EXPECT_TRUE(equal_queue(my_queue, true_queue));
  EXPECT_EQ(my_queue.front(), 3);
  my_queue.clear();
  ASSERT_ANY_THROW(my_queue.pop());
}

TEST(queue, Swap) {
  s21::queue<int> my_queue1{1, 2, 3, 4};
  s21::queue<int> my_queue2{6, 7, 8, 9, 10};
  my_queue1.swap(my_queue2);

  std::initializer_list<int> il1 = {1, 2, 3, 4};
  std::initializer_list<int> il2 = {6, 7, 8, 9, 10};
  std::queue<int> true_queue1{il1};
  std::queue<int> true_queue2{il2};
  true_queue1.swap(true_queue2);

  EXPECT_TRUE(equal_queue(my_queue1, true_queue1));
  EXPECT_TRUE(equal_queue(my_queue2, true_queue2));
}
TEST(queue, func_insert_many_back_1) {
  s21::queue<int> my_queue;
  std::queue<int> true_queue;

  for (int i = 1; i < 5; ++i) true_queue.push(i);

  my_queue.insert_many_back(1, 2, 3, 4);
  EXPECT_TRUE(equal_queue(my_queue, true_queue));
}