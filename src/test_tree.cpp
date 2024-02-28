#include "s21_containers.h"
#include <gtest/gtest.h>

#define EPS 1e-7

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

TEST(SetSuite, InitFromList) {
    std::set<int> trueSet = {50, 45, 1, 30, 49, 46, 55, 51, 53};
    Set<int> testSet({50, 45, 1, 30, 49, 46, 55, 51, 53});
    EXPECT_EQ(testSet.size(), trueSet.size());
    testSet.clear();
}

TEST(SetSuite, SetTests) {
    std::set<int> trueSet = {50, 45, 1, 30, 49, 46, 55, 51, 53};
    // for (int num : trueSet) {
    //     std::cout << num << " ";
    // }
    // std::cout << "\n ---- \n";

    Set<int> testSet({50, 45, 1, 30, 49, 46, 55, 51, 53});
    testSet.printAll();
    // std::cout << *(testSet.begin()) << std::endl;
    // testSet.printAll();
    
    EXPECT_EQ(testSet.size(), trueSet.size());
    testSet.clear();
}