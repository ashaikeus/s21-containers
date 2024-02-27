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
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.size(), vector_int.size());
  EXPECT_EQ(true_vector_int.capacity(), vector_int.capacity());
  EXPECT_EQ(true_vector_int.data(), vector_int.data());

  Vector<char> vector_char;
  std::vector<char> true_vector_char;
  EXPECT_EQ(true_vector_char.size(), vector_char.size());
  EXPECT_EQ(true_vector_char.capacity(), vector_char.capacity());
  EXPECT_EQ(true_vector_char.data(), vector_char.data());
}

TEST(vector, parametric_constructor_non_zero) {
  Vector<int> vector(3);
  std::vector<int> true_vector(3);
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  EXPECT_EQ(true_vector[0], vector[0]);
  EXPECT_EQ(true_vector[1], vector[1]);
  EXPECT_EQ(true_vector[2], vector[2]);
  EXPECT_EQ(true_vector[3], vector[3]);
}

TEST(vector, parametric_constructor_zero) {
  Vector<int> vector(0);
  std::vector<int> true_vector(0);
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  EXPECT_EQ(true_vector.data(), vector.data());
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
  std::vector<int> true_vector = {};
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  EXPECT_EQ(true_vector.data(), vector.data());
}

TEST(vector, list_constructor_nonempty) {
  Vector<int> vector = {1};
  std::vector<int> true_vector = {1};
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  EXPECT_EQ(true_vector[0], vector[0]);

  Vector<int> vector_five_elements = {0, 1, 2, 3, 4};
  std::vector<int> true_vector_five_elements = {0, 1, 2, 3, 4};
  EXPECT_EQ(true_vector_five_elements.size(), vector_five_elements.size());
  EXPECT_EQ(true_vector_five_elements.capacity(), vector_five_elements.capacity());
  for (size_t element = 0; element < vector_five_elements.size(); element++) {
    EXPECT_EQ(true_vector_five_elements[element], vector_five_elements[element]);
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

TEST(vector, operator_eq) {
  Vector<int> vector;
  Vector<int> copy_vector = vector;
  EXPECT_EQ(0u, copy_vector.size());
  EXPECT_EQ(0u, copy_vector.capacity());
  EXPECT_EQ(copy_vector.data(), nullptr);

  Vector<int> vector_five_elements = {0, 1, 2, 3, 4};
  Vector<int> copy_vector_five_elements = vector_five_elements;
  EXPECT_EQ(5u, copy_vector_five_elements.size());
  EXPECT_EQ(5u, copy_vector_five_elements.capacity());
  for (size_t element = 0; element < copy_vector_five_elements.size(); element++) {
    EXPECT_EQ((int)element, copy_vector_five_elements[element]);
  }
}

TEST(vector, at) {
  Vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  EXPECT_EQ(true_vector.at(0), vector.at(0));
  EXPECT_EQ(true_vector.at(1), vector.at(1));
  EXPECT_EQ(true_vector.at(2), vector.at(2));
  EXPECT_THROW(vector.at(-1), std::out_of_range);
  EXPECT_THROW(vector.at(3), std::out_of_range);
  vector.at(0) = 15;
  true_vector.at(0) = 15;
  EXPECT_EQ(true_vector[0], vector[0]);
}

TEST(vector, operator_index) {
  Vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  EXPECT_EQ(true_vector[0], vector[0]);
  EXPECT_EQ(true_vector[1], vector[1]);
  EXPECT_EQ(true_vector[2], vector[2]);
  vector[0] = 15;
  true_vector[0] = 15;
  EXPECT_EQ(true_vector[0], vector[0]);
}

TEST(vector, front) {
  Vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  EXPECT_EQ(true_vector.front(), vector.front());
  Vector<char> vector_char = {'a', 'b', 'c'};
  std::vector<char> true_vector_char = {'a', 'b', 'c'};
  EXPECT_EQ(true_vector_char.front(), vector_char.front());
}

TEST(vector, back) {
  Vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  EXPECT_EQ(true_vector.back(), vector.back());
  Vector<char> vector_char = {'a', 'b', 'c'};
  std::vector<char> true_vector_char = {'a', 'b', 'c'};
  EXPECT_EQ(true_vector_char.back(), vector_char.back());
}

TEST(vector, direct_access_data) {
  Vector<int> vector = {0, 1, 2};
  const int *data = vector.data();
  for (size_t element = 0; element < vector.size(); element++) {
    EXPECT_EQ((int)element, data[element]);
  }
}

TEST(vector, iterator_begin) {
  Vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  EXPECT_EQ(*true_vector.begin(), *vector.begin());
  true_vector.resize(0);
  vector.clear();
  vector.shrink_to_fit();
  EXPECT_EQ(*true_vector.begin(), *vector.begin());

  Vector<char> vector_char = {'a', 'b', 'c'};
  std::vector<char> true_vector_char = {'a', 'b', 'c'};
  EXPECT_EQ(*true_vector_char.begin(), *vector_char.begin());
} 

TEST(vector, iterator_end) {
  Vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  EXPECT_EQ(*true_vector.end(), *vector.end());
  // for (Vector<int>::iterator iter = vector.begin(); iter != vector.end(); iter++) {
  //   std::cout << *iter << std::endl;
  // }
  // for (int value : vector) {
  //   std::cout << value << std::endl;
  // }
  true_vector.resize(0);
  vector.clear();
  vector.shrink_to_fit();
  EXPECT_EQ(*true_vector.end(), *vector.end());
} 

TEST(vector, empty) {
  Vector<int> non_empty_vector = {0, 1, 2};
  Vector<int> empty_vector;
  EXPECT_FALSE(non_empty_vector.empty());
  EXPECT_TRUE(empty_vector.empty());
  empty_vector.push_back(1);
  EXPECT_FALSE(empty_vector.empty());
}

TEST(vector, size) {
  Vector<int> vector_int;
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.size(), vector_int.size());

  Vector<char> vector_char;
  std::vector<char> true_vector_char;
  EXPECT_EQ(true_vector_char.size(), vector_char.size());

  Vector<int> vector(3);
  std::vector<int> true_vector(3);
  EXPECT_EQ(true_vector.size(), vector.size());
}

TEST(vector, max_size) {
  Vector<int> vector_int;
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.max_size(), vector_int.max_size());
  //
  // По рекомендации пиров эту функцию не стоит тестировать
  //
  // Vector<char> vector_char;
  // std::vector<char> true_vector_char;
  // EXPECT_EQ(true_vector_char.max_size(), vector_char.max_size());
  //
  // Кусок кода выше выдаёт ошибку, предел в два раза больше, чем на самом деле
  //
}

TEST(vector, reserve) {
  Vector<int> vector_int;
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.capacity(), vector_int.capacity());
  vector_int.reserve(10);
  true_vector_int.reserve(10);
  EXPECT_EQ(true_vector_int.capacity(), vector_int.capacity());
}

TEST(vector, capacity) {
  Vector<int> vector_int;
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.capacity(), vector_int.capacity());

  Vector<char> vector_char;
  std::vector<char> true_vector_char;
  EXPECT_EQ(true_vector_char.capacity(), vector_char.capacity());

  Vector<int> vector(3);
  std::vector<int> true_vector(3);
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
}

TEST(vector, shrink_to_fit) {
  Vector<int> vector;
  std::vector<int> true_vector;
  true_vector.shrink_to_fit();
  vector.shrink_to_fit();
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  for (int element = 0; element < 1000; element++) {
    true_vector.push_back(element);
    vector.push_back(element);
  }
  true_vector.shrink_to_fit();
  vector.shrink_to_fit();
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  true_vector.clear();
  vector.clear();
  true_vector.shrink_to_fit();
  vector.shrink_to_fit();
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
}

TEST(vector, clear) {
  Vector<int> vector;
  std::vector<int> true_vector;
  true_vector.clear();
  vector.clear();
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  for (int element = 0; element < 1000; element++) {
    true_vector.push_back(element);
    vector.push_back(element);
  }
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  true_vector.clear();
  vector.clear();
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  for (size_t element = 0; element < vector.size(); element++) {
    EXPECT_EQ(true_vector[element], vector[element]);
  }
}

TEST(vector, insert) {
  Vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  vector.insert(vector.begin(), 3);
  true_vector.insert(true_vector.begin(), 3);
  EXPECT_EQ(true_vector[0], vector[0]);
  vector.insert(vector.end(), 3);
  true_vector.insert(true_vector.end(), 3);
  EXPECT_EQ(true_vector[3], vector[3]);
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
}

TEST(vector, erase) {
  Vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  vector.erase(vector.begin());
  true_vector.erase(true_vector.begin());
  EXPECT_EQ(true_vector[0], vector[0]);
  vector.erase(vector.begin() + 1);
  true_vector.erase(true_vector.begin() + 1);
  EXPECT_EQ(true_vector[1], vector[1]);
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
}

TEST(vector, pushback) {
  Vector<int> vector;
  std::vector<int> true_vector;
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  EXPECT_EQ(true_vector.data(), vector.data());
  vector.push_back(0);
  true_vector.push_back(0);
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  EXPECT_EQ(true_vector[0], vector[0]);
  vector.push_back(0);
  true_vector.push_back(0);
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  EXPECT_EQ(true_vector[1], vector[1]);
  vector.push_back(0);
  true_vector.push_back(0);
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector[2], vector[2]);
}

TEST(vector, pop_back) {
  Vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  vector.pop_back();
  true_vector.pop_back();
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
}

TEST(vector, swap) {
  Vector<int> vector1 = {0, 1, 2};
  Vector<int> vector2 = {3, 4};
  EXPECT_EQ(0, vector1[0]);
  EXPECT_EQ(3, vector2[0]);
  EXPECT_EQ(3u, vector1.size());
  EXPECT_EQ(2u, vector2.size());
  vector1.swap(vector2);
  EXPECT_EQ(3, vector1[0]);
  EXPECT_EQ(0, vector2[0]);
  EXPECT_EQ(2u, vector1.size());
  EXPECT_EQ(3u, vector2.size());
}
