#include <gtest/gtest.h>

#include "s21_containers.h"

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

TEST(vector, standart_constructor) {
  Vector<int> vector_int;
  EXPECT_EQ(0u, vector_int.size());
  EXPECT_EQ(0u, vector_int.capacity());
  EXPECT_EQ(vector_int.get_data_pointer(), nullptr);

  Vector<char> vector_char;
  EXPECT_EQ(0u, vector_char.size());
  EXPECT_EQ(0u, vector_char.capacity());
  EXPECT_EQ(vector_char.get_data_pointer(), nullptr);
}

TEST(vector, parametric_constructor_non_zero) {
  Vector<int> vector(3);
  EXPECT_EQ(3u, vector.size());
  EXPECT_EQ(3u, vector.capacity());
}

TEST(vector, parametric_constructor_zero) {
  Vector<int> vector(0);
  EXPECT_EQ(0u, vector.size());
  EXPECT_EQ(0u, vector.capacity());
  EXPECT_EQ(vector.get_data_pointer(), nullptr);
}

TEST(vector, parametric_constructor_negative) {
  try {
    Vector<int> vector(-3);
    FAIL();
  } catch (const std::exception& error) {
    EXPECT_EQ(error.what(), std::string("std::bad_alloc"));
  }
}

TEST(vector, list_constructor_empty) {
  Vector<int> vector = {};
  EXPECT_EQ(0u, vector.size());
  EXPECT_EQ(0u, vector.capacity());
  EXPECT_EQ(vector.get_data_pointer(), nullptr);
}

TEST(vector, list_constructor_nonempty) {
  Vector<int> vector_one_element = {1};
  EXPECT_EQ(1u, vector_one_element.size());
  EXPECT_EQ(1u, vector_one_element.capacity());

  Vector<int> vector_five_elements = {1, 2, 3, 4, 5};
  EXPECT_EQ(5u, vector_five_elements.size());
  EXPECT_EQ(5u, vector_five_elements.capacity());
}

// TEST(vector, list_constructor_error)
// {
//     try
//     {
//         Vector<int> vector = {1, 3};
//         FAIL();
//     }
//     catch(const std::exception& error)
//     {
//         EXPECT_EQ(error.what(), std::string("std::bad_alloc"));
//     }
// }