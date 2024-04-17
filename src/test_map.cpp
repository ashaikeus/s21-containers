#include "test.h"

TEST(MapSuite, InitFromList) {
  std::map<int, std::string> trueMap = {{50, "Elena"},  {45, "Michael"},
                                        {1, "Andrew"},  {30, "Kirill"},
                                        {49, "Lyubov"}, {46, "Victoria"}};
  s21::Map<int, std::string> testMap({{50, "Elena"},
                                      {45, "Michael"},
                                      {1, "Andrew"},
                                      {30, "Kirill"},
                                      {49, "Lyubov"},
                                      {46, "Victoria"}});
  EXPECT_EQ(testMap.size(), trueMap.size());
  testMap.clear();
}

TEST(MapSuite, InitAssign) {
  std::map<int, std::string> trueMap = {{50, "Elena"},  {45, "Michael"},
                                        {1, "Andrew"},  {30, "Kirill"},
                                        {49, "Lyubov"}, {46, "Victoria"}};
  s21::Map<int, std::string> testMap = {{50, "Elena"},  {45, "Michael"},
                                        {1, "Andrew"},  {30, "Kirill"},
                                        {49, "Lyubov"}, {46, "Victoria"}};
  EXPECT_EQ(testMap.size(), trueMap.size());
  testMap.clear();
}

TEST(MapSuite, InitCopy) {
  s21::Map<int, std::string> trueMap = {{50, "Elena"},  {45, "Michael"},
                                        {1, "Andrew"},  {30, "Kirill"},
                                        {49, "Lyubov"}, {46, "Victoria"}};
  s21::Map<int, std::string> testMap(trueMap);

  EXPECT_EQ(testMap.size(), trueMap.size());
  EXPECT_TRUE(trueMap == testMap);

  trueMap.clear();
  testMap.clear();
}

TEST(MapSuite, InitMove) {
  s21::Map<int, std::string> moveMap = {{50, "Elena"},  {45, "Michael"},
                                        {1, "Andrew"},  {30, "Kirill"},
                                        {49, "Lyubov"}, {46, "Victoria"}};
  s21::Map<int, std::string> testMap(std::move(moveMap));
  s21::Map<int, std::string> trueMap = {{50, "Elena"},  {45, "Michael"},
                                        {1, "Andrew"},  {30, "Kirill"},
                                        {49, "Lyubov"}, {46, "Victoria"}};
  EXPECT_EQ(testMap.size(), trueMap.size());
  EXPECT_EQ(0u, moveMap.size());
  EXPECT_TRUE(testMap == trueMap);
  moveMap.clear();
  testMap.clear();
  trueMap.clear();
}

TEST(MapSuite, Swap) {
  s21::Map<int, std::string> testMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> testMap2 = {
      {45, "Michael"}, {1, "Andrew"}, {30, "Kirill"}};
  s21::Map<int, std::string> resMap1 = {
      {45, "Michael"}, {1, "Andrew"}, {30, "Kirill"}};
  s21::Map<int, std::string> resMap2 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  testMap1.swap(testMap2);
  EXPECT_EQ(testMap1.size(), resMap1.size());
  EXPECT_EQ(testMap2.size(), resMap2.size());
  EXPECT_TRUE(testMap1 == resMap1);
  EXPECT_TRUE(testMap2 == resMap2);
  testMap1.clear();
  testMap2.clear();
  resMap1.clear();
  resMap2.clear();
}

TEST(MapSuite, Equal) {
  s21::Map<int, std::string> testMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> testMap2 = {
      {45, "Michael"}, {1, "Andrew"}, {30, "Kirill"}};
  s21::Map<int, std::string> testMap3 = {
      {45, "Michael"}, {1, "Andrew"}, {30, "Kirill"}};
  s21::Map<int, std::string> testMap4 = {
      {26, "Veronica"}, {210, "Raul"}, {35, "Arcade"}};
  EXPECT_TRUE(testMap2 == testMap3);
  EXPECT_FALSE(testMap1 == testMap3);
  EXPECT_FALSE(testMap2 == testMap4);
  testMap1.clear();
  testMap2.clear();
  testMap3.clear();
  testMap4.clear();
}

TEST(MapSuite, Begin) {
  std::map<int, std::string> trueMap = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> testMap = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  EXPECT_TRUE(testMap.begin().getCurrent()->key_ == trueMap.begin()->first);
  EXPECT_TRUE(testMap.begin().getCurrent()->value_ == trueMap.begin()->second);
  EXPECT_TRUE(testMap.cbegin().getCurrent()->key_ == trueMap.begin()->first);
  EXPECT_TRUE(testMap.cbegin().getCurrent()->value_ == trueMap.begin()->second);
  testMap.clear();
  trueMap.clear();
}

TEST(MapSuite, End) {
  s21::Map<int, std::string> testMap = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  EXPECT_EQ(testMap.end(), nullptr);
  EXPECT_EQ(testMap.cend(), nullptr);
  testMap.clear();
}

TEST(MapSuite, Empty) {
  s21::Map<int, std::string> testMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> testMap2;
  EXPECT_FALSE(testMap1.empty());
  EXPECT_TRUE(testMap2.empty());
  testMap1.clear();
  testMap2.clear();
}

TEST(MapSuite, Size) {
  s21::Map<int, std::string> testMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  std::map<int, std::string> trueMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> testMap2;
  EXPECT_EQ(testMap1.size(), trueMap1.size());
  EXPECT_EQ(testMap2.size(), 0u);
  testMap1.clear();
  trueMap1.clear();
  testMap2.clear();
}

TEST(MapSuite, MaxSize) {
  // По рекомендации пиров тестировать эту функцию не стоит
  //
  //  std::map<int, std::string> trueMap1;
  //   s21::Map<int, std::string> testMap1;
  //   EXPECT_EQ(testMap1.max_size(), trueMap1.max_size());
  //   std::map<char, char> trueMap2;
  //   s21::Map<char, char> testMap2;
  //   EXPECT_EQ(testMap2.max_size(), trueMap2.max_size());
  //   testMap1.clear();
  //   testMap2.clear();
}

TEST(MapSuite, Clear) {
  s21::Map<int, std::string> testMap = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> trueMap;
  EXPECT_EQ(testMap.size(), 4u);
  testMap.clear();
  EXPECT_EQ(testMap, trueMap);
  testMap.clear();
  trueMap.clear();
}

TEST(MapSuite, Insert) {
  s21::Map<int, std::string> testMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}};
  s21::Map<int, std::string> trueMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> testMap2;
  s21::Map<int, std::string> trueMap2 = {{13, "Diana"}};
  s21::Map<int, std::string> testMap3 = {{13, "Diana"}};
  s21::Map<int, std::string> trueMap3 = {{13, "Diana"}};
  EXPECT_TRUE(testMap1.insert({13, "Diana"}).second);
  EXPECT_TRUE(testMap2.insert({13, "Diana"}).second);
  EXPECT_FALSE(testMap3.insert({13, "Diana"}).second);
  EXPECT_EQ(testMap1.size(), trueMap1.size());
  EXPECT_EQ(testMap2.size(), trueMap2.size());
  EXPECT_EQ(testMap3.size(), trueMap3.size());
  EXPECT_EQ(testMap1, trueMap1);
  EXPECT_EQ(testMap2, trueMap2);
  EXPECT_EQ(testMap3, trueMap3);
  testMap1.clear();
  testMap2.clear();
  testMap3.clear();
  trueMap1.clear();
  trueMap2.clear();
  trueMap3.clear();
}

TEST(MapSuite, InsertByKeyValue) {
  s21::Map<int, std::string> testMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}};
  s21::Map<int, std::string> trueMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> testMap2;
  s21::Map<int, std::string> trueMap2 = {{13, "Diana"}};
  s21::Map<int, std::string> testMap3 = {{13, "Diana"}};
  s21::Map<int, std::string> trueMap3 = {{13, "Diana"}};
  EXPECT_TRUE(testMap1.insert(13, "Diana").second);
  EXPECT_TRUE(testMap2.insert(13, "Diana").second);
  EXPECT_FALSE(testMap3.insert(13, "Diana").second);
  EXPECT_EQ(testMap1.size(), trueMap1.size());
  EXPECT_EQ(testMap2.size(), trueMap2.size());
  EXPECT_EQ(testMap3.size(), trueMap3.size());
  EXPECT_EQ(testMap1, trueMap1);
  EXPECT_EQ(testMap2, trueMap2);
  EXPECT_EQ(testMap3, trueMap3);
  testMap1.clear();
  testMap2.clear();
  testMap3.clear();
  trueMap1.clear();
  trueMap2.clear();
  trueMap3.clear();
}

TEST(MapSuite, Erase) {
  s21::Map<int, std::string> testMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> trueMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}};
  s21::Map<int, std::string> testMap2 = {{13, "Diana"}};
  s21::Map<int, std::string> trueMap2;
  s21::Map<int, std::string> testMap3 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}};
  s21::Map<int, std::string> trueMap3 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}};
  s21::Map<int, std::string> testMap4({{2, "Irina"}, {3, "Vladimir"}});
  s21::Map<int, std::string> trueMap4({{2, "Irina"}});
  testMap1.erase(testMap1.find(13));
  testMap2.erase(testMap2.find(13));
  EXPECT_ANY_THROW(testMap3.erase(testMap3.find(13)));
  testMap4.erase(testMap4.find(3));
  EXPECT_ANY_THROW(testMap3.erase(nullptr));
  EXPECT_EQ(testMap1, trueMap1);
  EXPECT_EQ(testMap2, trueMap2);
  EXPECT_EQ(testMap3, trueMap3);
  EXPECT_EQ(testMap4, trueMap4);
  testMap1.clear();
  testMap2.clear();
  testMap3.clear();
  testMap4.clear();
  trueMap1.clear();
  trueMap2.clear();
  trueMap3.clear();
  trueMap4.clear();
}

TEST(MapSuite, Erase2) {
  s21::Map<int, std::string> testMap1 = {
      {35, "Arcade"}, {234, "Raul"},    {209, "Rex"}, {202, "Lily"},
      {37, "Cass"},   {27, "Veronica"}, {26, "Craig"}};
  s21::Map<int, std::string> trueMap1 = {{209, "Rex"}, {26, "Craig"}};
  testMap1.erase(testMap1.find(35));
  testMap1.erase(testMap1.find(234));
  testMap1.erase(testMap1.find(27));
  testMap1.erase(testMap1.find(202));
  testMap1.erase(testMap1.find(37));
  testMap1.clear();
  trueMap1.clear();

  s21::Map<int, std::string> testMap2 = {
      {50, "Elena"}, {55, "Mikhail"}, {56, "Svetoslava"}};
  s21::Map<int, std::string> trueMap2 = {{55, "Mikhail"}, {56, "Svetoslava"}};
  testMap2.erase(testMap2.find(50));
  EXPECT_EQ(testMap2, trueMap2);
  testMap2.clear();
  trueMap2.clear();

  s21::Map<int, std::string> testMap3 = {
      {50, "Elena"}, {55, "Mikhail"}, {56, "Svetoslava"}, {54, "Dmitriy"}};
  s21::Map<int, std::string> trueMap3 = {
      {50, "Elena"}, {56, "Svetoslava"}, {54, "Dmitriy"}};
  testMap3.erase(testMap3.find(55));
  EXPECT_EQ(testMap3, trueMap3);
  testMap3.clear();
  trueMap3.clear();

  s21::Map<int, std::string> testMap4 = {{50, "Elena"},      {55, "Mikhail"},
                                         {56, "Svetoslava"}, {54, "Dmitriy"},
                                         {9, "Andrew"},      {19, "Rose"}};
  s21::Map<int, std::string> trueMap4 = {{55, "Mikhail"},    {56, "Svetoslava"},
                                         {56, "Svetoslava"}, {54, "Dmitriy"},
                                         {9, "Andrew"},      {19, "Rose"}};
  testMap4.erase(testMap4.find(50));
  EXPECT_EQ(testMap4, trueMap4);
  testMap4.clear();
  trueMap4.clear();

  s21::Map<int, std::string> testMap7 = {
      {50, "Elena"}, {55, "Mikhail"}, {56, "Svetoslava"}};
  s21::Map<int, std::string> trueMap7 = {{50, "Elena"}, {56, "Svetoslava"}};
  testMap7.erase(testMap7.find(55));
  EXPECT_EQ(testMap7, trueMap7);
  testMap7.clear();
  trueMap7.clear();
}

TEST(MapSuite, Find) {
  s21::Map<int, std::string> testMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  std::map<int, std::string> trueMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> testMap2;
  EXPECT_EQ(testMap1.find(50).getCurrent()->key_, trueMap1.find(50)->first);
  EXPECT_EQ(testMap1.find(50).getCurrent()->value_, trueMap1.find(50)->second);
  EXPECT_ANY_THROW(testMap1.find(-1));
  EXPECT_ANY_THROW(testMap2.find(30));
  testMap1.clear();
  trueMap1.clear();
  testMap2.clear();
}

TEST(MapSuite, Contains) {
  s21::Map<int, std::string> testMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"}, {13, "Diana"}};
  s21::Map<int, std::string> testMap2;
  EXPECT_TRUE(testMap1.contains(50));
  EXPECT_TRUE(testMap1.contains(49));
  EXPECT_TRUE(testMap1.contains(46));
  EXPECT_TRUE(testMap1.contains(13));
  EXPECT_FALSE(testMap1.contains(-1));
  EXPECT_FALSE(testMap2.contains(30));
  testMap1.clear();
  testMap2.clear();
}

TEST(MapSuite, Merge) {
  s21::Map<int, std::string> testMap11 = {{50, "Elena"},
                                          {49, "Lyubov"},
                                          {46, "Victoria"},
                                          {13, "Diana"},
                                          {2, "Irina"}};
  s21::Map<int, std::string> testMap12 = {
      {45, "Michael"}, {1, "Andrew"}, {30, "Kirill"}, {1, "Arkadiy"}};
  s21::Map<int, std::string> trueMap1 = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"},
      {13, "Diana"}, {2, "Irina"},   {45, "Michael"},
      {1, "Andrew"}, {30, "Kirill"}, {1, "Arkadiy"}};
  s21::Map<int, std::string> testMap21 = {
      {45, "Michael"}, {1, "Andrew"}, {30, "Kirill"}, {1, "Arkadiy"}};
  s21::Map<int, std::string> testMap22;
  s21::Map<int, std::string> trueMap2 = {
      {45, "Michael"}, {1, "Andrew"}, {30, "Kirill"}, {1, "Arkadiy"}};
  testMap11.merge(testMap12);
  testMap21.merge(testMap22);
  EXPECT_EQ(testMap11, trueMap1);
  EXPECT_EQ(testMap21, trueMap2);
  testMap11.clear();
  testMap12.clear();
  trueMap1.clear();
  testMap21.clear();
  testMap22.clear();
  trueMap2.clear();
}

TEST(MapSuite, Brackets) {
  s21::Map<int, std::string> trueMap = {{50, "Elena"},
                                        {49, "Lyubov"},
                                        {46, "Victoria"},
                                        {13, "Diana"},
                                        {2, "Irina"}};
  s21::Map<int, std::string> testMap;
  testMap[50] = "Elena";
  testMap[49] = "Lyubov";
  testMap[46] = "Victoria";
  testMap[13] = "Diana";
  testMap[2] = "Vladimir";
  testMap[2] = "Irina";
  EXPECT_EQ(testMap, trueMap);
  testMap.clear();
  trueMap.clear();
}

TEST(MapSuite, At) {
  std::map<int, std::string> trueMap = {{50, "Elena"},
                                        {49, "Lyubov"},
                                        {46, "Victoria"},
                                        {13, "Diana"},
                                        {2, "Irina"}};
  s21::Map<int, std::string> testMap = {{50, "Elena"},
                                        {49, "Lyubov"},
                                        {46, "Victoria"},
                                        {13, "Diana"},
                                        {2, "Irina"}};
  EXPECT_EQ(testMap.at(50), trueMap.at(50));
  EXPECT_EQ(testMap.at(13), trueMap.at(13));
  EXPECT_ANY_THROW(testMap.at(-9));
  testMap.clear();
  trueMap.clear();
}

TEST(MapSuite, InsertOrAssign) {
  s21::Map<int, std::string> trueMap = {{50, "Elena"},
                                        {49, "Lyubov"},
                                        {46, "Victoria"},
                                        {13, "Diana"},
                                        {2, "Irina"}};
  s21::Map<int, std::string> testMap;
  testMap.insert_or_assign(50, "Elena");
  testMap.insert_or_assign(49, "Lyubov");
  testMap.insert_or_assign(46, "Victoria");
  testMap.insert_or_assign(13, "Diana");
  testMap.insert_or_assign(2, "Vladimir");
  testMap.insert_or_assign(2, "Irina");
  EXPECT_EQ(testMap, trueMap);
  testMap.clear();
  trueMap.clear();
}

TEST(MapSuite, Iterator) {
  std::map<int, std::string> trueMap = {{50, "Elena"},    {49, "Lyubov"},
                                        {46, "Victoria"}, {13, "Diana"},
                                        {57, "Lyudmila"}, {55, "Ekaterina"}};
  s21::Map<int, std::string> testMap = {{50, "Elena"},    {49, "Lyubov"},
                                        {46, "Victoria"}, {13, "Diana"},
                                        {57, "Lyudmila"}, {55, "Ekaterina"}};
  auto it = testMap.find(50);
  ++it;
  auto itrue = trueMap.find(50);
  ++itrue;
  EXPECT_FALSE(it.getCurrent() == nullptr);
  EXPECT_EQ(it.getCurrent()->key_, itrue->first);
  EXPECT_EQ(it.getCurrent()->value_, itrue->second);
  testMap.clear();
  trueMap.clear();
}

TEST(MapSuite, InsertMany) {
  s21::Map<int, std::string> testMap1 = {{50, "Elena"},
                                         {49, "Lyubov"},
                                         {46, "Victoria"},
                                         {13, "Diana"},
                                         {2, "Irina"}};
  s21::Map<int, std::string> testMap2 = {
      {45, "Michael"}, {1, "Andrew"}, {30, "Kirill"}, {1, "Arkadiy"}};
  s21::Map<int, std::string> trueMap = {
      {50, "Elena"}, {49, "Lyubov"}, {46, "Victoria"},
      {13, "Diana"}, {2, "Irina"},   {45, "Michael"},
      {1, "Andrew"}, {30, "Kirill"}, {1, "Arkadiy"}};
  testMap1.insert_many(testMap2);
  EXPECT_EQ(testMap1, trueMap);
  testMap1.clear();
  testMap2.clear();
  trueMap.clear();
}