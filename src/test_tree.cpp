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

TEST(SetSuite, InitCopy) {
    Set<int> trueSet({50, 45, 1, 30, 49, 46, 55, 51, 53});
    Set<int> testSet(trueSet);
    
    EXPECT_EQ(testSet.size(), trueSet.size());
    EXPECT_EQ(1, trueSet == testSet);

    trueSet.clear();
    testSet.clear();
}

TEST(SetSuite, InitMove) {
    Set<int> moveSet({50, 45, 1, 30});
    Set<int> testSet(std::move(moveSet));
    Set<int> trueSet({50, 45, 1, 30});
    EXPECT_EQ(testSet.size(), trueSet.size());
    EXPECT_EQ(0, moveSet.size());
    EXPECT_EQ(1, testSet == trueSet);
    moveSet.clear();
    testSet.clear();
    trueSet.clear();
}

TEST(SetSuite, Swap) {
    Set<int> testSet1({50, 45, 1, 30});
    Set<int> testSet2({49, 46, 55, 51, 53});
    Set<int> resSet1({49, 46, 55, 51, 53});
    Set<int> resSet2({50, 45, 1, 30});
    testSet1.swap(testSet2);
    EXPECT_EQ(testSet1.size(), resSet1.size());
    EXPECT_EQ(testSet2.size(), resSet2.size());
    EXPECT_EQ(1, testSet1 == resSet1);
    EXPECT_EQ(1, testSet2 == resSet2);
    testSet1.clear();
    testSet2.clear();
    resSet1.clear();
    resSet2.clear();
}

TEST(SetSuite, SetTests) {
    std::set<int> trueSet = {50, 45, 1, 30, 49, 46, 55, 51, 53};
    // for (int num : trueSet) {
    //     std::cout << num << " ";
    // }
    // std::cout << "\n ---- \n";

    Set<int> testSet({50, 45, 1, 30, 49, 46, 55, 51, 53});
    // testSet.printAll();
    // std::cout << *(testSet.begin()) << std::endl;
    // testSet.printAll();
    
    EXPECT_EQ(testSet.size(), trueSet.size());
    testSet.clear();
}