#include "test.h"

TEST(MultisetSuite, InitFromList) {
  std::multiset<int> trueMultiset = {50, 45, 1, 30, 49, 46, 55, 51, 53, 53};
  s21::Multiset<int> testMultiset = {50, 45, 1, 30, 49, 46, 55, 51, 53, 53};
  EXPECT_EQ(testMultiset.size(), trueMultiset.size());
  testMultiset.clear();
}

TEST(MultisetSuite, InitAssign) {
  std::multiset<int> trueMultiset = {50, 45, 1, 30, 49, 46, 55, 51, 53, 53};
  s21::Multiset<int> testMultiset =
      s21::Multiset({50, 45, 1, 30, 49, 46, 55, 51, 53, 53});
  s21::Multiset<int> testMultiset2 = testMultiset;
  EXPECT_EQ(testMultiset.size(), trueMultiset.size());
  EXPECT_EQ(testMultiset2.size(), trueMultiset.size());
  testMultiset.clear();
  testMultiset2.clear();
}

TEST(MultisetSuite, InitCopy) {
  s21::Multiset<int> trueMultiset({50, 45, 1, 30, 49, 46, 55, 51, 53, 53});
  s21::Multiset<int> testMultiset(trueMultiset);

  EXPECT_EQ(testMultiset.size(), trueMultiset.size());
  EXPECT_TRUE(trueMultiset == testMultiset);

  trueMultiset.clear();
  testMultiset.clear();
}

TEST(MultisetSuite, InitMove) {
  s21::Multiset<int> moveMultiset({50, 45, 1, 30, 1});
  s21::Multiset<int> testMultiset(std::move(moveMultiset));
  s21::Multiset<int> trueMultiset({50, 45, 1, 30, 1});
  EXPECT_EQ(testMultiset.size(), trueMultiset.size());
  EXPECT_EQ(0u, moveMultiset.size());
  EXPECT_TRUE(testMultiset == trueMultiset);
  moveMultiset.clear();
  testMultiset.clear();
  trueMultiset.clear();
}

TEST(MultisetSuite, Swap) {
  s21::Multiset<int> testMultiset1({50, 45, 1, 30, 1});
  s21::Multiset<int> testMultiset2({49, 46, 55, 51, 53, 53});
  s21::Multiset<int> resMultiset1({49, 46, 55, 51, 53, 53});
  s21::Multiset<int> resMultiset2({50, 45, 1, 30, 1});
  testMultiset1.swap(testMultiset2);
  EXPECT_EQ(testMultiset1.size(), resMultiset1.size());
  EXPECT_EQ(testMultiset2.size(), resMultiset2.size());
  EXPECT_TRUE(testMultiset1 == resMultiset1);
  EXPECT_TRUE(testMultiset2 == resMultiset2);
  testMultiset1.clear();
  testMultiset2.clear();
  resMultiset1.clear();
  resMultiset2.clear();
}

TEST(MultisetSuite, Equal) {
  s21::Multiset<int> testMultiset1({50, 45, 1, 30});
  s21::Multiset<int> testMultiset2({50, 45, 1, 30});
  s21::Multiset<int> testMultiset3({49, 46, 55, 51, 53, 53});
  s21::Multiset<int> testMultiset4({50, 45, 1, 30, 30});
  EXPECT_TRUE(testMultiset1 == testMultiset2);
  EXPECT_FALSE(testMultiset1 == testMultiset3);
  EXPECT_FALSE(testMultiset1 == testMultiset4);
  testMultiset1.clear();
  testMultiset2.clear();
  testMultiset3.clear();
  testMultiset4.clear();
}

TEST(MultisetSuite, Begin) {
  s21::Multiset<int> testMultiset({50, 45, 1, 30});
  std::multiset<int> trueMultiset({50, 45, 1, 30});
  EXPECT_TRUE(*testMultiset.begin() == *trueMultiset.begin());
  EXPECT_TRUE(*testMultiset.cbegin() == *trueMultiset.begin());
  testMultiset.clear();
  trueMultiset.clear();
}

TEST(MultisetSuite, End) {
  s21::Multiset<int> testMultiset({50, 45, 1, 30});
  EXPECT_ANY_THROW(*testMultiset.end());
  EXPECT_ANY_THROW(*testMultiset.cend());
  testMultiset.clear();
}

TEST(MultisetSuite, Empty) {
  s21::Multiset<int> testMultiset1({50, 45, 1, 30});
  s21::Multiset<int> testMultiset2;
  EXPECT_FALSE(testMultiset1.empty());
  EXPECT_TRUE(testMultiset2.empty());
  testMultiset1.clear();
  testMultiset2.clear();
}

TEST(MultisetSuite, Size) {
  s21::Multiset<int> testMultiset1({50, 45, 1, 30});
  std::multiset<int> trueMultiset1({50, 45, 1, 30});
  s21::Multiset<int> testMultiset2;
  EXPECT_EQ(testMultiset1.size(), trueMultiset1.size());
  EXPECT_EQ(testMultiset2.size(), 0u);
  testMultiset1.clear();
  trueMultiset1.clear();
  testMultiset2.clear();
}

TEST(MultisetSuite, MaxSize) {
  // По рекомендации пиров тестировать эту функцию не стоит
  //
  // std::multiset<int> trueMultiset1;
  // s21::Multiset<int> testMultiset1;
  // EXPECT_EQ(testMultiset1.max_size(), trueMultiset1.max_size());
  // std::multiset<char> trueMultiset2;
  // s21::Multiset<char> testMultiset2;
  // EXPECT_EQ(testMultiset2.max_size(), trueMultiset2.max_size());
  // testMultiset1.clear();
  // testMultiset2.clear();
}

TEST(MultisetSuite, Clear) {
  s21::Multiset<int> testMultiset({50, 45, 1, 30});
  s21::Multiset<int> trueMultiset;
  EXPECT_EQ(testMultiset.size(), 4u);
  testMultiset.clear();
  EXPECT_EQ(testMultiset, trueMultiset);
  testMultiset.clear();
  trueMultiset.clear();
}

TEST(MultisetSuite, Insert) {
  s21::Multiset<int> testMultiset1(
      {50, 45, 1, 2, 2, 1, 1, 1, 3, 4, 4, 5, 6, 3, 5, 6});
  s21::Multiset<int> trueMultiset1(
      {50, 45, 1, 2, 2, 1, 1, 1, 3, 4, 4, 5, 6, 3, 5, 6, 30});
  s21::Multiset<int> testMultiset2;
  s21::Multiset<int> trueMultiset2({30});
  s21::Multiset<int> testMultiset3({30});
  s21::Multiset<int> trueMultiset3({30, 30});
  testMultiset1.insert(30);
  testMultiset2.insert(30);
  testMultiset3.insert(30);
  EXPECT_EQ(testMultiset1, trueMultiset1);
  EXPECT_EQ(testMultiset2, trueMultiset2);
  EXPECT_EQ(testMultiset3, trueMultiset3);
  testMultiset1.clear();
  testMultiset2.clear();
  testMultiset3.clear();
  trueMultiset1.clear();
  trueMultiset2.clear();
  trueMultiset3.clear();
}

TEST(MultisetSuite, Erase) {
  // delete root with 2, root with 1, root with 0
  //        normal with 2, normal with 1, leaf

  s21::Multiset<int> testSet1({50, 55, 45, 1, 30});  // root with 2
  s21::Multiset<int> trueSet1({55, 45, 1, 30});
  testSet1.erase(testSet1.find(50));
  EXPECT_EQ(testSet1, trueSet1);
  testSet1.clear();
  trueSet1.clear();

  s21::Multiset<int> testSet2({50, 45, 1, 30});  // root with 1
  s21::Multiset<int> trueSet2({45, 1, 30});
  testSet2.erase(testSet2.find(50));
  EXPECT_EQ(testSet2, trueSet2);
  testSet2.clear();
  trueSet2.clear();

  s21::Multiset<int> testSet3({50});  // root with 0
  s21::Multiset<int> trueSet3;
  testSet3.erase(testSet3.find(50));
  EXPECT_EQ(testSet3, trueSet3);
  testSet3.clear();
  trueSet3.clear();

  s21::Multiset<int> testSet4({50, 55, 45, 1, 30, 46});  // normal with 2
  s21::Multiset<int> trueSet4({50, 55, 1, 30, 46});
  testSet4.erase(testSet4.find(45));
  EXPECT_EQ(testSet4, trueSet4);
  testSet4.clear();
  trueSet4.clear();

  s21::Multiset<int> testSet5({50, 55, 45, 1, 30, 46});  // normal with 1
  s21::Multiset<int> trueSet5({50, 55, 45, 30, 46});
  testSet5.erase(testSet5.find(1));
  EXPECT_EQ(testSet5, trueSet5);
  testSet5.clear();
  trueSet5.clear();

  s21::Multiset<int> testSet6({50, 55, 45, 1, 30, 46});  // normal with 0
  s21::Multiset<int> trueSet6({50, 55, 45, 1, 46});
  testSet6.erase(testSet6.find(30));
  EXPECT_EQ(testSet6, trueSet6);
  testSet6.clear();
  trueSet6.clear();
}

TEST(MultisetSuite, Erase2) {
  // delete dup root with 2
  //        dup normal with 2, dup normal with 1
  s21::Multiset<int> testSet1({50, 55, 50, 45, 1, 30});  // dup root with 2
  s21::Multiset<int> trueSet1({55, 50, 45, 1, 30});
  testSet1.erase(testSet1.find(50));
  EXPECT_EQ(testSet1, trueSet1);
  testSet1.clear();
  trueSet1.clear();

  s21::Multiset<int> testSet4(
      {50, 55, 45, 1, 45, 30, 46});  // dup normal with 2
  s21::Multiset<int> trueSet4({50, 55, 1, 45, 30, 46});
  testSet4.erase(testSet4.find(45));
  EXPECT_EQ(testSet4, trueSet4);
  testSet4.clear();
  trueSet4.clear();

  s21::Multiset<int> testSet5({50, 55, 45, 1, 30, 1, 46});  // dup normal with 1
  s21::Multiset<int> trueSet5;
  testSet5.erase(testSet5.find(1));
  testSet5.erase(testSet5.find(50));
  testSet5.erase(testSet5.find(55));
  testSet5.erase(testSet5.find(45));
  testSet5.erase(testSet5.find(30));
  testSet5.erase(testSet5.find(1));
  testSet5.erase(testSet5.find(46));
  EXPECT_EQ(testSet5, trueSet5);
  testSet5.clear();
  trueSet5.clear();

  s21::Multiset<int> testSet6({50, 55, 45, 46});
  s21::Multiset<int> trueSet6({50, 55, 46});
  testSet6.erase(testSet6.find(45));
  EXPECT_EQ(testSet6, trueSet6);
  testSet6.clear();
  trueSet6.clear();

  s21::Multiset<int> testSet7({50, 55, 56});
  s21::Multiset<int> trueSet7({50, 56});
  testSet7.erase(testSet7.find(55));
  EXPECT_EQ(testSet7, trueSet7);
  testSet7.clear();
  trueSet7.clear();

  s21::Multiset<int> testSet8({50, 55, 56, 54});
  s21::Multiset<int> trueSet8({50, 56, 54});
  testSet8.erase(testSet8.find(55));
  EXPECT_EQ(testSet8, trueSet8);
  testSet8.clear();
  trueSet8.clear();

  EXPECT_ANY_THROW(testSet6.erase(nullptr));
}

TEST(MultisetSuite, Find) {
  s21::Multiset<int> testMultiset1({50, 45, 1, 30});
  std::multiset<int> trueMultiset1({50, 45, 1, 30});
  s21::Multiset<int> testMultiset2;
  EXPECT_EQ(*testMultiset1.find(30), *trueMultiset1.find(30));
  EXPECT_ANY_THROW(*testMultiset1.find(-1));
  EXPECT_ANY_THROW(*testMultiset2.find(30));
  testMultiset1.clear();
  trueMultiset1.clear();
  testMultiset2.clear();
}

TEST(MultisetSuite, Contains) {
  s21::Multiset<int> testMultiset1({50, 45, 1, 30});
  s21::Multiset<int> testMultiset2;
  EXPECT_TRUE(testMultiset1.contains(1));
  EXPECT_TRUE(testMultiset1.contains(45));
  EXPECT_TRUE(testMultiset1.contains(50));
  EXPECT_TRUE(testMultiset1.contains(30));
  EXPECT_FALSE(testMultiset1.contains(-1));
  EXPECT_FALSE(testMultiset2.contains(30));
  testMultiset1.clear();
  testMultiset2.clear();
}

TEST(MultisetSuite, Merge) {
  s21::Multiset<int> testMultiset11({50, 45, 1, 30});
  s21::Multiset<int> testMultiset12({49, 46, 55, 51, 53});
  s21::Multiset<int> trueMultiset1({50, 45, 1, 30, 49, 46, 55, 51, 53});
  s21::Multiset<int> testMultiset21({50, 45, 1, 30});
  s21::Multiset<int> testMultiset22;
  s21::Multiset<int> trueMultiset2({50, 45, 1, 30});
  testMultiset11.merge(testMultiset12);
  testMultiset21.merge(testMultiset22);
  EXPECT_EQ(testMultiset11, trueMultiset1);
  EXPECT_EQ(testMultiset21, trueMultiset2);
  testMultiset11.clear();
  testMultiset12.clear();
  trueMultiset1.clear();
  testMultiset21.clear();
  testMultiset22.clear();
  trueMultiset2.clear();
}

TEST(MultisetSuite, Count) {
  s21::Multiset<int> testMultiset1({50, 45, 1, 30});
  std::multiset<int> trueMultiset1({50, 45, 1, 30});
  s21::Multiset<int> testMultiset2({50, 45, 1, 30, 1, 1, 30, 1, 45, 3});
  std::multiset<int> trueMultiset2({50, 45, 1, 30, 1, 1, 30, 1, 45, 3});
  s21::Multiset<int> testMultiset3;
  EXPECT_EQ(testMultiset1.count(30), trueMultiset1.count(30));
  EXPECT_EQ(testMultiset2.count(30), trueMultiset2.count(30));
  EXPECT_EQ(testMultiset3.count(30), 0u);
  trueMultiset1.clear();
  testMultiset1.clear();
  trueMultiset2.clear();
  testMultiset2.clear();
  testMultiset3.clear();
}

TEST(MultisetSuite, EqualRangeBounds) {
  s21::Multiset<int> testMultiset1({50, 45, 1, 30});
  std::multiset<int> trueMultiset1({50, 45, 1, 30});
  s21::Multiset<int> testMultiset2({50, 45, 1, 30, 1, 1, 30, 1, 45, 3});
  std::multiset<int> trueMultiset2({50, 45, 1, 30, 1, 1, 30, 1, 45, 3});
  s21::Multiset<int> testMultiset3;
  EXPECT_EQ(*testMultiset1.equal_range(30).first,
            *trueMultiset1.equal_range(30).first);
  EXPECT_EQ(*testMultiset1.equal_range(30).second,
            *trueMultiset1.equal_range(30).second);
  EXPECT_EQ(*testMultiset2.equal_range(30).first,
            *trueMultiset2.equal_range(30).first);
  EXPECT_EQ(*testMultiset2.equal_range(30).second,
            *trueMultiset2.equal_range(30).second);
  EXPECT_EQ(*testMultiset2.equal_range(1).first,
            *trueMultiset2.equal_range(1).first);
  EXPECT_EQ(*testMultiset2.equal_range(1).second,
            *trueMultiset2.equal_range(1).second);
  EXPECT_ANY_THROW(*testMultiset3.equal_range(30).first);
  EXPECT_ANY_THROW(*testMultiset3.equal_range(30).second);
  trueMultiset1.clear();
  testMultiset1.clear();
  trueMultiset2.clear();
  testMultiset2.clear();
  testMultiset3.clear();
}

TEST(MultisetSuite, InsertMany) {
  s21::Multiset<int> testSet1({50, 45, 1, 30, 30});
  s21::Multiset<int> testSet2({49, 46, 55, 51, 53, 53});
  s21::Multiset<int> trueSet({50, 45, 1, 30, 30, 49, 46, 55, 51, 53, 53});
  testSet1.insert_many(testSet2);
  EXPECT_EQ(testSet1, trueSet);
  testSet1.clear();
  testSet2.clear();
  trueSet.clear();
}