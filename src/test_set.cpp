#include "test.h"

TEST(SetSuite, InitFromList) {
  std::set<int> trueSet = {50, 45, 1, 30, 49, 46, 55, 51, 53};
  s21::Set<int> testSet({50, 45, 1, 30, 49, 46, 55, 51, 53});
  EXPECT_EQ(testSet.size(), trueSet.size());
  testSet.clear();
}

TEST(SetSuite, InitAssign) {
  std::set<int> trueSet = {50, 45, 1, 30, 49, 46, 55, 51, 53};
  s21::Set<int> testSet = s21::Set({50, 45, 1, 30, 49, 46, 55, 51, 53});
  EXPECT_EQ(testSet.size(), trueSet.size());
  testSet.clear();
}

TEST(SetSuite, InitCopy) {
  s21::Set<int> trueSet({50, 45, 1, 30, 49, 46, 55, 51, 53});
  s21::Set<int> testSet(trueSet);

  EXPECT_EQ(testSet.size(), trueSet.size());
  EXPECT_TRUE(trueSet == testSet);

  trueSet.clear();
  testSet.clear();
}

TEST(SetSuite, InitMove) {
  s21::Set<int> moveSet({50, 45, 1, 30});
  s21::Set<int> testSet(std::move(moveSet));
  s21::Set<int> trueSet({50, 45, 1, 30});
  EXPECT_EQ(testSet.size(), trueSet.size());
  EXPECT_EQ(0u, moveSet.size());
  EXPECT_TRUE(testSet == trueSet);
  moveSet.clear();
  testSet.clear();
  trueSet.clear();
}

TEST(SetSuite, Swap) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> testSet2({49, 46, 55, 51, 53});
  s21::Set<int> resSet1({49, 46, 55, 51, 53});
  s21::Set<int> resSet2({50, 45, 1, 30});
  testSet1.swap(testSet2);
  EXPECT_EQ(testSet1.size(), resSet1.size());
  EXPECT_EQ(testSet2.size(), resSet2.size());
  EXPECT_TRUE(testSet1 == resSet1);
  EXPECT_TRUE(testSet2 == resSet2);
  testSet1.clear();
  testSet2.clear();
  resSet1.clear();
  resSet2.clear();
}

TEST(SetSuite, Equal) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> testSet2({50, 45, 1, 30});
  s21::Set<int> testSet3({49, 46, 55, 51, 53});
  EXPECT_TRUE(testSet1 == testSet2);
  EXPECT_FALSE(testSet1 == testSet3);
  testSet1.clear();
  testSet2.clear();
  testSet3.clear();
}

TEST(SetSuite, Begin) {
  s21::Set<int> testSet({50, 45, 1, 30});
  std::set<int> trueSet({50, 45, 1, 30});
  EXPECT_TRUE(*testSet.begin() == *trueSet.begin());
  EXPECT_TRUE(*testSet.cbegin() == *trueSet.begin());
  testSet.clear();
  trueSet.clear();
}

TEST(SetSuite, End) {
  s21::Set<int> testSet({50, 45, 1, 30});
  EXPECT_ANY_THROW(*testSet.end());
  EXPECT_ANY_THROW(*testSet.cend());
  testSet.clear();
}

TEST(SetSuite, Empty) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> testSet2;
  EXPECT_FALSE(testSet1.empty());
  EXPECT_TRUE(testSet2.empty());
  testSet1.clear();
  testSet2.clear();
}

TEST(SetSuite, Size) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  std::set<int> trueSet1({50, 45, 1, 30});
  s21::Set<int> testSet2;
  EXPECT_EQ(testSet1.size(), trueSet1.size());
  EXPECT_EQ(testSet2.size(), 0u);
  testSet1.clear();
  trueSet1.clear();
  testSet2.clear();
}

TEST(SetSuite, MaxSize) {
  // По рекомендации пиров тестировать эту функцию не стоит
  //
  // std::set<int> trueSet1;
  // s21::Set<int> testSet1;
  // EXPECT_EQ(testSet1.max_size(), trueSet1.max_size());
  // std::set<char> trueSet2;
  // s21::Set<char> testSet2;
  // EXPECT_EQ(testSet2.max_size(), trueSet2.max_size());
  // testSet1.clear();
  // testSet2.clear();
}

TEST(SetSuite, Clear) {
  s21::Set<int> testSet({50, 45, 1, 30});
  s21::Set<int> trueSet;
  EXPECT_EQ(testSet.size(), 4u);
  testSet.clear();
  EXPECT_EQ(testSet, trueSet);
  testSet.clear();
  trueSet.clear();
}

TEST(SetSuite, Insert) {
  s21::Set<int> testSet1({50, 45, 1});
  s21::Set<int> trueSet1({50, 45, 1, 30});
  s21::Set<int> testSet2;
  s21::Set<int> trueSet2({30});
  s21::Set<int> testSet3({30});
  s21::Set<int> trueSet3({30});
  EXPECT_TRUE(testSet1.insert(30).second);
  EXPECT_TRUE(testSet2.insert(30).second);
  EXPECT_FALSE(testSet3.insert(30).second);
  EXPECT_EQ(testSet1.size(), trueSet1.size());
  EXPECT_EQ(testSet2.size(), trueSet2.size());
  EXPECT_EQ(testSet3.size(), trueSet3.size());
  testSet1.clear();
  testSet2.clear();
  testSet3.clear();
  trueSet1.clear();
  trueSet2.clear();
  trueSet3.clear();
}

TEST(SetSuite, Erase) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> trueSet1({50, 45, 1});
  s21::Set<int> testSet2({30});
  s21::Set<int> trueSet2;
  s21::Set<int> testSet3({1, 2, 3});
  s21::Set<int> trueSet3({1, 2, 3});
  s21::Set<int> testSet4({2, 1});
  s21::Set<int> trueSet4({2});
  s21::Set<int> testSet5({2, 1, 3, 4, 8, 9});
  s21::Set<int> trueSet5;
  testSet1.erase(testSet1.find(30));
  testSet2.erase(testSet2.find(30));
  EXPECT_ANY_THROW(testSet3.erase(testSet3.find(30)));
  testSet4.erase(testSet4.find(1));
  testSet5.erase(testSet5.find(1));
  testSet5.erase(testSet5.find(2));
  testSet5.erase(testSet5.find(3));
  testSet5.erase(testSet5.find(4));
  testSet5.erase(testSet5.find(8));
  testSet5.erase(testSet5.find(9));
  EXPECT_ANY_THROW(testSet5.erase(testSet5.find(9)));
  EXPECT_EQ(testSet1, trueSet1);
  EXPECT_EQ(testSet2, trueSet2);
  EXPECT_EQ(testSet3, trueSet3);
  EXPECT_EQ(testSet4, trueSet4);
  EXPECT_EQ(testSet5, trueSet5);
  testSet1.clear();
  testSet2.clear();
  testSet3.clear();
  testSet4.clear();
  testSet5.clear();
  trueSet1.clear();
  trueSet2.clear();
  trueSet3.clear();
  trueSet4.clear();
  trueSet5.clear();
}

TEST(SetSuite, Erase2) {
  // delete root with 2, root with 1, root with 0
  //        normal with 2, normal with 1, leaf

  s21::Set<int> testSet1({50, 55, 45, 1, 30});  // root with 2
  s21::Set<int> trueSet1({55, 45, 1, 30});
  testSet1.erase(testSet1.find(50));
  EXPECT_EQ(testSet1, trueSet1);
  testSet1.clear();
  trueSet1.clear();

  s21::Set<int> testSet2({50, 45, 1, 30});  // root with 1
  s21::Set<int> trueSet2({45, 1, 30});
  testSet2.erase(testSet2.find(50));
  EXPECT_EQ(testSet2, trueSet2);
  testSet2.clear();
  trueSet2.clear();

  s21::Set<int> testSet3({50});  // root with 0
  s21::Set<int> trueSet3;
  testSet3.erase(testSet3.find(50));
  EXPECT_EQ(testSet3, trueSet3);
  testSet3.clear();
  trueSet3.clear();

  s21::Set<int> testSet4({50, 55, 45, 1, 30, 46});  // normal with 2
  s21::Set<int> trueSet4({50, 55, 1, 30, 46});
  testSet4.erase(testSet4.find(45));
  EXPECT_EQ(testSet4, trueSet4);
  testSet4.clear();
  trueSet4.clear();

  s21::Set<int> testSet5({50, 55, 45, 1, 30, 46});  // normal with 1
  s21::Set<int> trueSet5({50, 55, 45, 30, 46});
  testSet5.erase(testSet5.find(1));
  EXPECT_EQ(testSet5, trueSet5);
  testSet5.clear();
  trueSet5.clear();

  s21::Set<int> testSet6({50, 55, 45, 1, 30, 46});  // normal with 0
  s21::Set<int> trueSet6({50, 55, 45, 1, 46});
  testSet6.erase(testSet6.find(30));
  EXPECT_EQ(testSet6, trueSet6);
  testSet6.clear();
  trueSet6.clear();

  s21::Set<int> testSet7({50, 55, 56});
  s21::Set<int> trueSet7({50, 56});
  testSet7.erase(testSet7.find(55));
  EXPECT_EQ(testSet7, trueSet7);
  testSet7.clear();
  trueSet7.clear();

  s21::Set<int> testSet8({50, 55, 56, 54});
  s21::Set<int> trueSet8({50, 56, 54});
  testSet8.erase(testSet8.find(55));
  EXPECT_EQ(testSet8, trueSet8);
  testSet8.clear();
  trueSet8.clear();

  EXPECT_ANY_THROW(testSet6.erase(nullptr));
}

TEST(SetSuite, Find) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  std::set<int> trueSet1({50, 45, 1, 30});
  s21::Set<int> testSet2;
  EXPECT_EQ(*testSet1.find(30), *trueSet1.find(30));
  EXPECT_ANY_THROW(*testSet1.find(-1));
  EXPECT_ANY_THROW(*testSet2.find(30));
  testSet1.clear();
  trueSet1.clear();
  testSet2.clear();
}

TEST(SetSuite, Contains) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> testSet2;
  EXPECT_TRUE(testSet1.contains(1));
  EXPECT_TRUE(testSet1.contains(45));
  EXPECT_TRUE(testSet1.contains(50));
  EXPECT_TRUE(testSet1.contains(30));
  EXPECT_FALSE(testSet1.contains(-1));
  EXPECT_FALSE(testSet2.contains(30));
  testSet1.clear();
  testSet2.clear();
}

TEST(SetSuite, Merge) {
  s21::Set<int> testSet11({50, 45, 1, 30});
  s21::Set<int> testSet12({49, 46, 55, 51, 53});
  s21::Set<int> trueSet1({50, 45, 1, 30, 49, 46, 55, 51, 53});
  s21::Set<int> testSet21({50, 45, 1, 30});
  s21::Set<int> testSet22;
  s21::Set<int> trueSet2({50, 45, 1, 30});
  testSet11.merge(testSet12);
  testSet21.merge(testSet22);
  EXPECT_EQ(testSet11, trueSet1);
  EXPECT_EQ(testSet21, trueSet2);
  testSet11.clear();
  testSet12.clear();
  trueSet1.clear();
  testSet21.clear();
  testSet22.clear();
  trueSet2.clear();
}

TEST(SetSuite, InsertMany) {
  s21::Set<int> testSet1({50, 45, 1, 30});
  s21::Set<int> testSet2({49, 46, 55, 51, 53});
  s21::Set<int> trueSet({50, 45, 1, 30, 49, 46, 55, 51, 53});
  testSet1.insert_many(testSet2);
  EXPECT_EQ(testSet1, trueSet);
  testSet1.clear();
  testSet2.clear();
  trueSet.clear();
}