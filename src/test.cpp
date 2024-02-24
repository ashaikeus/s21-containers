#include <iostream>
#include <gtest/gtest.h>

#include "s21_containers.h"

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(vector, constructor) {
    Vector<int> v = {1, 2, 3, 4, 5};
    v.push_back(6);
    for (int i = 0; i < v.size(); i++) {
       std::cout << v.at(i); 
    }
    std::cout << std::endl;

}
