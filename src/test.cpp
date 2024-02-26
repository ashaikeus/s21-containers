#include "s21_containers.h"
#include <gtest/gtest.h>

#define EPS 1e-7

template<typename T>
void print_vector(const Vector<T>& vector) {
    for (size_t element = 0; element < vector.size(); element++) {
        std::cout << vector[element] << std::endl;
    }
    std::cout << "###################\n";
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

TEST(vector, standart_constructor) {
  Vector<int> vector_int;
  EXPECT_EQ(0u, vector_int.size());
  EXPECT_EQ(0u, vector_int.capacity());
  EXPECT_EQ(vector_int.data(), nullptr);

  Vector<char> vector_char;
  EXPECT_EQ(0u, vector_char.size());
  EXPECT_EQ(0u, vector_char.capacity());
  EXPECT_EQ(vector_char.data(), nullptr);
}

TEST(vector, parametric_constructor_non_zero) {
  Vector<int> vector(3);
  EXPECT_EQ(3u, vector.size());
  EXPECT_EQ(3u, vector.capacity());
  EXPECT_EQ(0, vector[0]);
  EXPECT_EQ(0, vector[1]);
  EXPECT_EQ(0, vector[2]);
//   EXPECT_EQ(0, vector[3]); ???
//   EXPECT_THROW(vector[3], std::out_of_range);
}

TEST(vector, parametric_constructor_zero) {
  Vector<int> vector(0);
  EXPECT_EQ(0u, vector.size());
  EXPECT_EQ(0u, vector.capacity());
  EXPECT_EQ(vector.data(), nullptr);
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
  EXPECT_EQ(vector.data(), nullptr);
}

TEST(vector, list_constructor_nonempty) {
  Vector<int> vector_one_element = {1};
  EXPECT_EQ(1u, vector_one_element.size());
  EXPECT_EQ(1u, vector_one_element.capacity());
  EXPECT_EQ(1, vector_one_element[0]);

  Vector<int> vector_five_elements = {0, 1, 2, 3, 4};
  EXPECT_EQ(5u, vector_five_elements.size());
  EXPECT_EQ(5u, vector_five_elements.capacity());
  for (size_t element = 0; element < vector_five_elements.size(); element++) {
    EXPECT_EQ((int)element, vector_five_elements[element]);
  }
}

TEST(vector, copy_constructor) {
  Vector<int> vector;
  Vector<int> copy_vector(vector);
  EXPECT_EQ(0u, copy_vector.size());
  EXPECT_EQ(0u, copy_vector.capacity());
  EXPECT_EQ(copy_vector.data(), nullptr);

  Vector<int> vector_five_elements = {0, 1, 2, 3, 4};
  Vector<int> copy_vector_five_elements(vector_five_elements);
  EXPECT_EQ(5u, copy_vector_five_elements.size());
  EXPECT_EQ(5u, copy_vector_five_elements.capacity());
  for (size_t element = 0; element < copy_vector_five_elements.size(); element++) {
    EXPECT_EQ((int)element, copy_vector_five_elements[element]);
  }
}

TEST(vector, move_constructor) {
  Vector<int> vector_five_elements = {0, 1, 2, 3, 4};
  Vector<int> move_vector_five_elements(std::move(vector_five_elements));

  EXPECT_EQ(0u, vector_five_elements.size());
  EXPECT_EQ(0u, vector_five_elements.capacity());
  EXPECT_EQ(vector_five_elements.data(), nullptr);

  EXPECT_EQ(5u, move_vector_five_elements.size());
  EXPECT_EQ(5u, move_vector_five_elements.capacity());
  for (size_t element = 0; element < move_vector_five_elements.size(); element++) {
    EXPECT_EQ((int)element, move_vector_five_elements[element]);
  }
}

TEST(vector, at) {
  Vector<int> vector = {0, 1, 2};
  EXPECT_EQ(0, vector.at(0));
  EXPECT_EQ(1, vector.at(1));
  EXPECT_EQ(2, vector.at(2));
  EXPECT_THROW(vector.at(-1), std::out_of_range);
  EXPECT_THROW(vector.at(3), std::out_of_range);
  vector.at(0) = 15;
  EXPECT_EQ(15, vector.at(0));
}

TEST(vector, operator_index) {
  Vector<int> vector = {0, 1, 2};
  EXPECT_EQ(0, vector[0]);
  EXPECT_EQ(1, vector[1]);
  EXPECT_EQ(2, vector[2]);
  vector[0] = 15;
  EXPECT_EQ(15, vector[0]);
}

TEST(vector, front) {
  Vector<int> vector = {0, 1, 2};
  EXPECT_EQ(0, vector.front());
  Vector<char> vector_char = {'a', 'b', 'c'};
  EXPECT_EQ('a', vector_char.front());
}

TEST(vector, pushback) {
  Vector<int> vector;
  EXPECT_EQ(0u, vector.size());
  EXPECT_EQ(0u, vector.capacity());
  EXPECT_EQ(vector.data(), nullptr);
  vector.push_back(0);
  EXPECT_EQ(1u, vector.size());
  EXPECT_EQ(2u, vector.capacity());
  EXPECT_EQ(0, vector[0]);
  vector.push_back(0);
  EXPECT_EQ(2u, vector.size());
  EXPECT_EQ(4u, vector.capacity());
  EXPECT_EQ(0, vector[1]);
  vector.push_back(0);
  EXPECT_EQ(3u, vector.size());
  EXPECT_EQ(4u, vector.capacity());
  EXPECT_EQ(0, vector[2]);
}
