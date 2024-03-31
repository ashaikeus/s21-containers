#include "test.h"
#include <list>

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

TEST(list, initilazer_constructor) {
    std::list<int> true_list = {0, 1, 2};
    s21::list<int> s21_list = {0, 1, 2};
    EXPECT_EQ(s21_list.size(), true_list.size());
    EXPECT_EQ(s21_list.empty(), true_list.empty());
    EXPECT_EQ(s21_list.front(), true_list.front());
    EXPECT_EQ(s21_list.back(), true_list.back());
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
    for (auto pointer = s21_list.begin(); pointer != nullptr; ++pointer, value++) {
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
    for (auto pointer = s21_list.begin(); pointer != nullptr; ++pointer, value++) {
        EXPECT_EQ(value, pointer.node_pointer()->value);
    }
    value = 2;
    for (auto pointer = s21_list.end(); pointer != nullptr; --pointer, value--) {
        EXPECT_EQ(value, pointer.node_pointer()->value);
    }
}

TEST(list, pop_back) {
    s21::list<int> s21_list = {0, 1, 2, 999};
    s21_list.pop_back();
    int value = 0;
    for (auto pointer = s21_list.begin(); pointer != nullptr; ++pointer, value++) {
        EXPECT_EQ(value, pointer.node_pointer()->value);
    }
    value = 2;
    for (auto pointer = s21_list.end(); pointer != nullptr; --pointer, value--) {
        EXPECT_EQ(value, pointer.node_pointer()->value);
    }
}

TEST(list, push_front) {
    s21::list<int> s21_list = {1, 2, 3};
    s21_list.push_front(0);
    int value = 0;
    for (auto pointer = s21_list.begin(); pointer != nullptr; ++pointer, value++) {
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
    for (auto pointer = s21_list.begin(); pointer != nullptr; ++pointer, value++) {
        EXPECT_EQ(value, pointer.node_pointer()->value);
    }
    value = 2;
    for (auto pointer = s21_list.end(); pointer != nullptr; --pointer, value--) {
        EXPECT_EQ(value, pointer.node_pointer()->value);
    }
}

TEST(list, swap) {
    s21::list<int> s21_list1 = {0, 1, 2};
    s21::list<int> s21_list2 = {1, 2, 3};
    s21_list1.swap(s21_list2);
    int value = 1;
    for (auto pointer = s21_list1.begin(); pointer != nullptr; ++pointer, value++) {
        EXPECT_EQ(value, pointer.node_pointer()->value);
    }
    value = 0;
    for (auto pointer = s21_list2.begin(); pointer != nullptr; ++pointer, value++) {
        EXPECT_EQ(value, pointer.node_pointer()->value);
    }
}

TEST(list, merge) {
    s21::list<int> s21_list = {0, 1, 2};
    s21::list<int> s21_list2 = {3, 4, 5};
    s21_list.merge(s21_list2);
    int value = 0;
    for (auto pointer = s21_list.begin(); pointer != nullptr; ++pointer, value++) {
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
    for (auto pointer = s21_list.begin(); pointer != nullptr; ++pointer, value++) {
        std::cout << pointer.node_pointer()->value << std::endl;
        EXPECT_EQ(value, pointer.node_pointer()->value);
    }
    EXPECT_EQ(value, 6);

}