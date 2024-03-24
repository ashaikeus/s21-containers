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
    EXPECT_EQ(s21_list.front(), true_list.front());
    EXPECT_EQ(s21_list.back(), true_list.back());
}
