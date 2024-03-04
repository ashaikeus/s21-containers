#include "s21_containersplus.h"
#include "test.h"

using namespace std;

TEST(array, standart_constructor) {
  s21::array<int, 4> array_int;
  array<int, 4> true_array_int;

  //   s21::array<int, 0> array2_int;
  //   EXPECT_TRUE(array2_int.begin() == nullptr);
  //   array<int, 0> true_array2;
  //   EXPECT_TRUE(true_array2.begin() == nullptr);

  EXPECT_EQ(array_int.size(), true_array_int.size());

  s21::array<int, 3> array_fl{2, 3};
  EXPECT_EQ(array_fl[0], 2);
  EXPECT_EQ(array_fl[1], 3);
  EXPECT_EQ(array_fl[2], 0);
  EXPECT_EQ(array_fl.size(), 3);
}
TEST(array, initializer_list_constructor) {
  array<int, 3> true_array_int{2, 3};
  s21::array<int, 3> array_fl{2, 3};

  EXPECT_EQ(array_fl[0], 2);
  EXPECT_EQ(array_fl[1], 3);
  EXPECT_EQ(array_fl[2], 0);
  EXPECT_EQ(array_fl.size(), 3);

  EXPECT_EQ(array_fl.size(), true_array_int.size());
  EXPECT_EQ(array_fl[1], true_array_int[1]);
  EXPECT_EQ(array_fl[2], true_array_int[2]);

  //   s21::array<int, 3> array_init2{2, 3, 4, 5};
}

TEST(array, copy_move_constructor) {
  s21::array<int, 4> array_int{2, 3};
  s21::array<int, 4> array_fl(array_int);
  EXPECT_EQ(array_fl[0], 2);
  EXPECT_EQ(array_fl[1], 3);
  EXPECT_EQ(array_fl[2], 0);
  EXPECT_EQ(array_fl.size(), 4);

  EXPECT_EQ(array_fl.size(), array_int.size());
  EXPECT_EQ(array_fl[1], array_int[1]);
  EXPECT_EQ(array_fl[2], array_int[2]);

  s21::array<int, 4> array_move2{1, 2, 3, 4};
  s21::array<int, 4> array_move(move(array_move2));
  EXPECT_EQ(array_move[1], array_move2[1]);
  EXPECT_EQ(array_move[3], array_move2[3]);
}

TEST(array, at_reference) {
  s21::array<int, 4> array_int{2, 3};
  EXPECT_EQ(array_int.at(0), 2);
  EXPECT_EQ(array_int.at(1), 3);
  ASSERT_ANY_THROW(array_int.at(7));
  ASSERT_ANY_THROW(array_int.at(-4));

  //   try {
  //     array_int.at(4);
  //   } catch (std::out_of_range& ex) {
  //     cerr << ex.what();
  //   }
}

TEST(array, front_back_reference) {
  array<int, 3> array_int = {33, 11, 22};
  s21::array<int, 3> true_array_int = {33, 11, 22};

  EXPECT_EQ(array_int.front(), true_array_int.front());
  EXPECT_EQ(array_int.back(), true_array_int.back());
}

TEST(array, data_reference) {
  array<int, 5> true_array_int = {5, 4, 3, 2, 1};
  s21::array<int, 5> array_int = {5, 4, 3, 2, 1};

  const int* data = array_int.data();
  for (size_t element = 0; element < array_int.size(); element++) {
    EXPECT_EQ(array_int[element], data[element]);
  }

  EXPECT_EQ(array_int.data(), &array_int[0]);
  EXPECT_EQ(true_array_int.data(), &true_array_int[0]);
}

TEST(array, empty_bool) {
  s21::array<int, 5> array_int = {5, 4, 3, 2, 1};
  array<int, 5> true_array_int = {5, 4, 3, 2, 1};
  EXPECT_EQ(array_int.empty(), true_array_int.empty());

  s21::array<int, 0> array_int2;
  array<int, 0> true_array_int2;
  EXPECT_EQ(array_int2.empty(), true_array_int2.empty());
}

TEST(array, max_size_function) {
  array<int, 5> true_array_int = {5, 4, 3, 2, 1};
  s21::array<int, 5> array_int = {5, 4, 3, 2, 1};
  EXPECT_EQ(true_array_int.max_size(), array_int.max_size());
  EXPECT_EQ(array_int.max_size(), array_int.size());

  array<int, 0> true_array_int2;
  s21::array<int, 0> array_int2;
  EXPECT_EQ(array_int2.max_size(), true_array_int2.max_size());
}

TEST(array, fill_function) {
  array<int, 5> true_array_int = {5, 4, 3, 2, 1};
  s21::array<int, 5> array_int = {5, 4, 3, 2, 1};

  true_array_int.fill(10);
  array_int.fill(10);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(true_array_int[i], array_int[i]);
}