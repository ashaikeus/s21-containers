#include <list>

#include "test.h"

template <typename T>
void print_list(const std::list<T>& list) {
  for (auto value : list) {
    std::cout << value << std::endl;
  }
}

TEST(list, constructor) {
  std::list<int> true_list;
  s21::list<int> s21_list;
  EXPECT_EQ(s21_list.size(), true_list.size());
  EXPECT_EQ(s21_list.empty(), true_list.empty());
}

TEST(list, constructor_n) {
  std::list<int> true_list(7);
  s21::list<int> s21_list(7);
  EXPECT_EQ(s21_list.size(), true_list.size());
  EXPECT_EQ(s21_list.empty(), true_list.empty());
  EXPECT_EQ(s21_list.front(), true_list.front());
  EXPECT_EQ(s21_list.back(), true_list.back());
}

TEST(list, initilazer_constructor) {
  std::list<int> true_list = {0, 1, 2};
  s21::list<int> s21_list = {0, 1, 2};
  EXPECT_EQ(s21_list.size(), true_list.size());
  EXPECT_EQ(s21_list.empty(), true_list.empty());
  EXPECT_EQ(s21_list.front(), true_list.front());
  EXPECT_EQ(s21_list.back(), true_list.back());
}

TEST(list, copy_constructor) {
  std::list<int> true_list = {0, 1, 2};
  s21::list<int> s21_copy_list = {0, 1, 2};
  s21::list<int> s21_list = s21_copy_list;
  EXPECT_EQ(s21_list.size(), true_list.size());
  EXPECT_EQ(s21_list.empty(), true_list.empty());
  EXPECT_EQ(s21_list.front(), true_list.front());
  EXPECT_EQ(s21_list.back(), true_list.back());
  int value = 0;
  for (auto pointer = s21_list.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
}

TEST(list, move_constructor) {
  std::list<int> true_list = {0, 1, 2};
  s21::list<int> s21_move_list = {0, 1, 2};
  s21::list<int> s21_list = std::move(s21_move_list);
  EXPECT_EQ(s21_list.size(), true_list.size());
  EXPECT_EQ(s21_list.empty(), true_list.empty());
  EXPECT_EQ(s21_list.front(), true_list.front());
  EXPECT_EQ(s21_list.back(), true_list.back());
  int value = 0;
  for (auto pointer = s21_list.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
  EXPECT_EQ(s21_move_list.size(), 0u);
  EXPECT_EQ(s21_move_list.empty(), true);
}

TEST(list, clear) {
  std::list<int> true_list;
  s21::list<int> s21_list = {0, 1, 2};
  s21_list.clear();
  EXPECT_EQ(s21_list.size(), true_list.size());
  EXPECT_EQ(s21_list.empty(), true_list.empty());
}

TEST(list, insert) {
  s21::list<int> s21_list = {0, 1, 3};
  // for (auto pointer = s21_list.begin(); pointer != nullptr; ++pointer) {
  //     std::cout << pointer.node_pointer()->value << std::endl;
  // }
  auto iter = s21_list.begin();
  ++iter;
  s21_list.insert(iter, 2);
  int value = 0;
  for (auto pointer = s21_list.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
  value = 3;
  for (auto pointer = s21_list.end(); pointer != nullptr; --pointer, value--) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
}

TEST(list, erase) {
  s21::list<int> s21_list = {0, 1, 999, 2};
  auto iter = s21_list.begin();
  ++iter;
  ++iter;
  s21_list.erase(iter);
  int value = 0;
  for (auto pointer = s21_list.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
  value = 2;
  for (auto pointer = s21_list.end(); pointer != nullptr; --pointer, value--) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
}

TEST(list, push_back) {
  s21::list<int> s21_list = {0, 1, 2};
  s21_list.push_back(3);
  int value = 0;
  for (auto pointer = s21_list.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
  value = 3;
  for (auto pointer = s21_list.end(); pointer != nullptr; --pointer, value--) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
}

TEST(list, pop_back) {
  s21::list<int> s21_list = {0, 1, 2, 999};
  s21_list.pop_back();
  int value = 0;
  for (auto pointer = s21_list.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
  value = 2;
  for (auto pointer = s21_list.end(); pointer != nullptr; --pointer, value--) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
}

TEST(list, pop_back_size_1) {
  s21::list<int> s21_list = {999};
  s21_list.pop_back();
  EXPECT_EQ(s21_list.empty(), true);
}

TEST(list, push_front) {
  s21::list<int> s21_list;
  s21_list.push_front(3);
  s21_list.push_front(2);
  s21_list.push_front(1);
  s21_list.push_front(0);
  int value = 0;
  for (auto pointer = s21_list.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
  value = 3;
  for (auto pointer = s21_list.end(); pointer != nullptr; --pointer, value--) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
}

TEST(list, pop_front) {
  s21::list<int> s21_list = {999, 0, 1, 2};
  s21_list.pop_front();
  int value = 0;
  for (auto pointer = s21_list.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
  value = 2;
  for (auto pointer = s21_list.end(); pointer != nullptr; --pointer, value--) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
}

TEST(list, pop_front_size_1) {
  s21::list<int> s21_list = {999};
  s21_list.pop_front();
  EXPECT_EQ(s21_list.empty(), true);
}

TEST(list, swap) {
  s21::list<int> s21_list1 = {0, 1, 2};
  s21::list<int> s21_list2 = {1, 2, 3};
  s21_list1.swap(s21_list2);
  int value = 1;
  for (auto pointer = s21_list1.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
  value = 0;
  for (auto pointer = s21_list2.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
}

TEST(list, merge) {
  s21::list<int> s21_list = {0, 1, 2};
  s21::list<int> s21_list2 = {3, 4, 5};
  s21_list.merge(s21_list2);
  int value = 0;
  for (auto pointer = s21_list.begin(); pointer != nullptr;
       ++pointer, value++) {
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
  EXPECT_EQ(value, 6);
}

TEST(list, splice) {
  s21::list<int> s21_list = {0, 1, 5};
  s21::list<int> s21_list2 = {2, 3, 4};
  auto iter = s21_list.end();
  --iter;
  s21_list.splice(iter, s21_list2);
  int value = 0;
  for (auto pointer = s21_list.begin(); pointer != nullptr;
       ++pointer, value++) {
    // std::cout << pointer.node_pointer()->value << std::endl;
    EXPECT_EQ(value, pointer.node_pointer()->value);
  }
  EXPECT_EQ(value, 6);
}

TEST(list, reverse) {
  s21::list<int> s21_list = {0, 1, 2, 15, 52, 9};
  s21::list<int> s21_reversed = {9, 52, 15, 2, 1, 0};
  s21_list.reverse();
  for (auto l = s21_list.begin(), r = s21_reversed.begin();
       l != nullptr || r != nullptr; ++l, ++r) {
    EXPECT_EQ(l.node_pointer()->value, r.node_pointer()->value);
  }
}

TEST(list, unique) {
  s21::list<int> s21_list = {0, 1, 2, 2, 2, 15, 15, 52, 15, 9};
  s21::list<int> s21_true = {0, 1, 2, 15, 52, 15, 9};
  s21_list.unique();
  for (auto l = s21_list.begin(), r = s21_true.begin();
       l != nullptr || r != nullptr; ++l, ++r) {
    EXPECT_EQ(l.node_pointer()->value, r.node_pointer()->value);
  }
}

TEST(list, sort) {
  s21::list<int> s21_list = {0, 1, 2, 15, 52, 15, 9, -27};
  s21::list<int> s21_true = {-27, 0, 1, 2, 9, 15, 15, 52};
  s21_list.sort();
  for (auto l = s21_list.begin(), r = s21_true.begin();
       l != nullptr || r != nullptr; ++l, ++r) {
    EXPECT_EQ(l.node_pointer()->value, r.node_pointer()->value);
  }
}