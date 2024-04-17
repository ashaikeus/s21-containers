#include "test.h"

using namespace std;

TEST(array, standart_constructor) {
  s21::array<int, 4> array_int;
  array<int, 4> true_array_int;

  EXPECT_EQ(array_int.size(), true_array_int.size());

  s21::array<int, 3> array_fl{2, 3};
  EXPECT_EQ(array_fl[0], 2);
  EXPECT_EQ(array_fl[1], 3);
  EXPECT_EQ(array_fl[2], 0);
  EXPECT_EQ(array_fl.size(), 3u);
}

TEST(array, initializer_list_constructor) {
  array<int, 3> true_array_int{2, 3};
  s21::array<int, 3> array_fl{2, 3};
  s21::array<int, 3> array_fl2 = {2, 3};
  array_fl2 = array_fl;

  EXPECT_EQ(array_fl[0], 2);
  EXPECT_EQ(array_fl[1], 3);
  EXPECT_EQ(array_fl[2], 0);
  EXPECT_EQ(array_fl.size(), 3u);

  EXPECT_EQ(array_fl.size(), true_array_int.size());
  EXPECT_EQ(array_fl[1], true_array_int[1]);
  EXPECT_EQ(array_fl[2], true_array_int[2]);

  try {
    s21::array<int, 3> array_init2{2, 3, 4, 5};
  } catch (std::exception& ex) {
    EXPECT_EQ(ex.what(), std::string("too many initializer values"));
  }
}

TEST(array, copy_move_constructor) {
  s21::array<int, 4> array_int{2, 3};
  s21::array<int, 4> array_fl(array_int);
  EXPECT_EQ(array_fl[0], 2);
  EXPECT_EQ(array_fl[1], 3);
  EXPECT_EQ(array_fl[2], 0);
  EXPECT_EQ(array_fl.size(), 4u);

  EXPECT_EQ(array_fl.size(), array_int.size());
  EXPECT_EQ(array_fl[1], array_int[1]);
  EXPECT_EQ(array_fl[2], array_int[2]);

  s21::array<int, 4> array_move2{1, 2, 3, 4};
  s21::array<int, 4> array_move(std::move(array_move2));
  EXPECT_EQ(array_move[1], array_move2[1]);
  EXPECT_EQ(array_move[3], array_move2[3]);
}

TEST(array, at_reference) {
  s21::array<int, 4> array_int{2, 3};
  EXPECT_EQ(array_int.at(0), 2);
  EXPECT_EQ(array_int.at(1), 3);
  ASSERT_ANY_THROW(array_int.at(7));
  ASSERT_ANY_THROW(array_int.at(-4));

  try {
    array_int.at(4);
  } catch (std::exception& ex) {
    EXPECT_EQ(ex.what(), string("index is out of range"));
  }

  s21::array<string, 4> array_string{"Hello", ",", "world", "!"};
  EXPECT_EQ(array_string.at(0), "Hello");
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

TEST(array, swap_function) {
  array<int, 5> true_array_int = {3, 3, 2, 2, 1};
  s21::array<int, 5> array_int = {3, 3, 2, 2, 1};

  array<int, 5> true_array_int2 = {1, 1, 1, 2, 3};
  s21::array<int, 5> array_int2 = {1, 1, 1, 2, 3};

  true_array_int.swap(true_array_int2);
  array_int.swap(array_int2);

  int* j = true_array_int.begin();
  for (int* i = array_int.begin(); i < array_int.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
  EXPECT_EQ(true_array_int2[0], array_int2[0]);

  s21::array<string, 4> array_string{"set", "me", "from", "21"};
  s21::array<string, 4> array_string2{"Hello", ",", "world", "!"};

  array_string2.swap(array_string);

  EXPECT_EQ(array_string2[3], "21");
  EXPECT_EQ(array_string[0], "Hello");
  EXPECT_EQ(array_string[1], ",");
  EXPECT_EQ(array_string[2], "world");
  EXPECT_EQ(array_string[3], "!");
}

TEST(array, fill_function) {
  array<int, 5> true_array_int = {5, 4, 3, 2, 1};
  s21::array<int, 5> array_int = {5, 4, 3, 2, 1};

  true_array_int.fill(10);
  array_int.fill(10);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(true_array_int[i], array_int[i]);
}

TEST(array, zero_constructor) {
  s21::array<int, 0> array_int;
  array<int, 0> true_array;

  EXPECT_THROW(array_int.front(), std::invalid_argument);
  EXPECT_THROW(array_int.back(), std::invalid_argument);

  EXPECT_TRUE(true_array.data() == nullptr);
  EXPECT_TRUE(array_int.data() == nullptr);

  EXPECT_TRUE(array_int.begin() == nullptr);
  EXPECT_TRUE(true_array.begin() == nullptr);

  EXPECT_TRUE(true_array.end() == nullptr);
  EXPECT_TRUE(array_int.end() == nullptr);

  EXPECT_EQ(array_int.size(), true_array.size());
  EXPECT_EQ(array_int.max_size(), true_array.max_size());

  EXPECT_EQ(array_int.empty(), true_array.empty());
}

TEST(array, swap_fill_zero_function) {
  array<int, 0> true_array_int;
  s21::array<int, 0> array_int;

  array<int, 0> true_array_int2;
  s21::array<int, 0> array_int2;

  true_array_int.swap(true_array_int2);
  array_int.swap(array_int2);

  true_array_int2.fill(2);
  array_int2.fill(2);

  EXPECT_THROW(array_int2.at(0), std::out_of_range);
  EXPECT_THROW(true_array_int2.at(0), std::out_of_range);
}