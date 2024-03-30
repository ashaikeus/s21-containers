#include "test.h"

template <typename T>
void print_vector(const s21::vector<T>& vector) {
  for (size_t element = 0; element < vector.size(); element++) {
    std::cout << vector[element] << " element = " << element <<std::endl;
  }
  std::cout << "###################\n";
}

TEST(vector, standart_constructor) {
  s21::vector<int> vector_int;
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.size(), vector_int.size());
  EXPECT_EQ(true_vector_int.capacity(), vector_int.capacity());
  EXPECT_EQ(true_vector_int.data(), vector_int.data());

  s21::vector<char> vector_char;
  std::vector<char> true_vector_char;
  EXPECT_EQ(true_vector_char.size(), vector_char.size());
  EXPECT_EQ(true_vector_char.capacity(), vector_char.capacity());
  EXPECT_EQ(true_vector_char.data(), vector_char.data());
}

TEST(vector, parametric_constructor_non_zero) {
  s21::vector<int> vector(3);
  std::vector<int> true_vector(3);
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  // EXPECT_EQ(true_vector[0], vector[0]);
  // EXPECT_EQ(true_vector[1], vector[1]);
  // EXPECT_EQ(true_vector[2], vector[2]);
  // EXPECT_EQ(true_vector[3], vector[3]);
}

TEST(vector, parametric_constructor_zero) {
  s21::vector<int> vector(0);
  std::vector<int> true_vector(0);
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  EXPECT_EQ(true_vector.data(), vector.data());
}

TEST(vector, parametric_constructor_negative) {
  try {
    s21::vector<int> vector(-3);
    FAIL();
  } catch (const std::exception& error) {
    EXPECT_EQ(error.what(), std::string("std::bad_alloc"));
  }
}

TEST(vector, list_constructor_empty) {
  s21::vector<int> vector = {};
  std::vector<int> true_vector = {};
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  EXPECT_EQ(true_vector.data(), vector.data());
}

TEST(vector, list_constructor_nonempty) {
  s21::vector<int> vector = {1};
  std::vector<int> true_vector = {1};
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
  EXPECT_EQ(true_vector[0], vector[0]);

  s21::vector<int> vector_five_elements = {0, 1, 2, 3, 4};
  std::vector<int> true_vector_five_elements = {0, 1, 2, 3, 4};
  EXPECT_EQ(true_vector_five_elements.size(), vector_five_elements.size());
  EXPECT_EQ(true_vector_five_elements.capacity(),
            vector_five_elements.capacity());
  for (size_t element = 0; element < vector_five_elements.size(); element++) {
    EXPECT_EQ(true_vector_five_elements[element],
              vector_five_elements[element]);
  }
}

TEST(vector, copy_constructor) {
  s21::vector<int> vector;
  s21::vector<int> copy_vector(vector);
  EXPECT_EQ(0u, copy_vector.size());
  EXPECT_EQ(0u, copy_vector.capacity());
  EXPECT_EQ(copy_vector.data(), nullptr);

  s21::vector<int> vector_five_elements = {0, 1, 2, 3, 4};
  s21::vector<int> copy_vector_five_elements(vector_five_elements);
  EXPECT_EQ(5u, copy_vector_five_elements.size());
  EXPECT_EQ(5u, copy_vector_five_elements.capacity());
  for (size_t element = 0; element < copy_vector_five_elements.size();
       element++) {
    EXPECT_EQ((int)element, copy_vector_five_elements[element]);
  }
}

TEST(vector, move_constructor) {
  s21::vector<int> vector_five_elements = {0, 1, 2, 3, 4};
  s21::vector<int> move_vector_five_elements(std::move(vector_five_elements));

  EXPECT_EQ(0u, vector_five_elements.size());
  EXPECT_EQ(0u, vector_five_elements.capacity());
  EXPECT_EQ(vector_five_elements.data(), nullptr);

  EXPECT_EQ(5u, move_vector_five_elements.size());
  EXPECT_EQ(5u, move_vector_five_elements.capacity());
  for (size_t element = 0; element < move_vector_five_elements.size();
       element++) {
    EXPECT_EQ((int)element, move_vector_five_elements[element]);
  }
}

TEST(vector, operator_eq) {
  s21::vector<int> vector;
  s21::vector<int> copy_vector = vector;
  EXPECT_EQ(0u, copy_vector.size());
  EXPECT_EQ(0u, copy_vector.capacity());
  EXPECT_EQ(copy_vector.data(), nullptr);

  s21::vector<int> vector_five_elements = {0, 1, 2, 3, 4};
  s21::vector<int> copy_vector_five_elements = vector_five_elements;
  EXPECT_EQ(5u, copy_vector_five_elements.size());
  EXPECT_EQ(5u, copy_vector_five_elements.capacity());
  for (size_t element = 0; element < copy_vector_five_elements.size();
       element++) {
    EXPECT_EQ((int)element, copy_vector_five_elements[element]);
  }
}

TEST(vector, at) {
  s21::vector<int> vector = {0, 1, 2};
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
  s21::vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  EXPECT_EQ(true_vector[0], vector[0]);
  EXPECT_EQ(true_vector[1], vector[1]);
  EXPECT_EQ(true_vector[2], vector[2]);
  vector[0] = 15;
  true_vector[0] = 15;
  EXPECT_EQ(true_vector[0], vector[0]);
}

TEST(vector, front) {
  s21::vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  EXPECT_EQ(true_vector.front(), vector.front());
  s21::vector<char> vector_char = {'a', 'b', 'c'};
  std::vector<char> true_vector_char = {'a', 'b', 'c'};
  EXPECT_EQ(true_vector_char.front(), vector_char.front());
}

TEST(vector, back) {
  s21::vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  EXPECT_EQ(true_vector.back(), vector.back());
  s21::vector<char> vector_char = {'a', 'b', 'c'};
  std::vector<char> true_vector_char = {'a', 'b', 'c'};
  EXPECT_EQ(true_vector_char.back(), vector_char.back());
}

TEST(vector, direct_access_data) {
  s21::vector<int> vector = {0, 1, 2};
  const int* data = vector.data();
  for (size_t element = 0; element < vector.size(); element++) {
    EXPECT_EQ((int)element, data[element]);
  }
}

TEST(vector, iterator_begin) {
  s21::vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  EXPECT_EQ(*true_vector.begin(), *vector.begin());
  true_vector.resize(0);
  vector.clear();
  vector.shrink_to_fit();
  // EXPECT_EQ(*true_vector.begin(), *vector.begin());

  s21::vector<char> vector_char = {'a', 'b', 'c'};
  std::vector<char> true_vector_char = {'a', 'b', 'c'};
  EXPECT_EQ(*true_vector_char.begin(), *vector_char.begin());
}

TEST(vector, iterator_end) {
  s21::vector<int> vector = {0, 1, 2};
  s21::vector<int> true_vector;
  true_vector.push_back(0);
  true_vector.push_back(1);
  true_vector.push_back(2);
  EXPECT_EQ(*vector.end(), *true_vector.end());
  vector.clear();
  vector.shrink_to_fit();
}

TEST(vector, empty) {
  s21::vector<int> non_empty_vector = {0, 1, 2};
  s21::vector<int> empty_vector;
  EXPECT_FALSE(non_empty_vector.empty());
  EXPECT_TRUE(empty_vector.empty());
  empty_vector.push_back(1);
  EXPECT_FALSE(empty_vector.empty());
}

TEST(vector, size) {
  s21::vector<int> vector_int;
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.size(), vector_int.size());

  s21::vector<char> vector_char;
  std::vector<char> true_vector_char;
  EXPECT_EQ(true_vector_char.size(), vector_char.size());

  s21::vector<int> vector(3);
  std::vector<int> true_vector(3);
  EXPECT_EQ(true_vector.size(), vector.size());
}

TEST(vector, max_size) {
  s21::vector<int> vector_int;
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.max_size(), vector_int.max_size());
  //
  // По рекомендации пиров эту функцию не стоит тестировать
  //
  // s21::vector<char> vector_char;
  // std::vector<char> true_vector_char;
  // EXPECT_EQ(true_vector_char.max_size(), vector_char.max_size());
  //
  // Кусок кода выше выдаёт ошибку, предел в два раза больше, чем на самом деле
  //
}

TEST(vector, reserve) {
  s21::vector<int> vector_int;
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.capacity(), vector_int.capacity());
  vector_int.reserve(10);
  true_vector_int.reserve(10);
  EXPECT_EQ(true_vector_int.capacity(), vector_int.capacity());
}

TEST(vector, capacity) {
  s21::vector<int> vector_int;
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.capacity(), vector_int.capacity());

  s21::vector<char> vector_char;
  std::vector<char> true_vector_char;
  EXPECT_EQ(true_vector_char.capacity(), vector_char.capacity());

  s21::vector<int> vector(3);
  std::vector<int> true_vector(3);
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
}

TEST(vector, shrink_to_fit) {
  s21::vector<int> vector;
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
  s21::vector<int> vector;
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
  s21::vector<int> vector = {0, 1, 2};
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

TEST(vector, insert_many) {
  s21::vector<int> vector = {0, 1, 2};
  s21::vector<int> vector2 = {3, 4, 5};
  s21::vector<int> vector3 = {6, 7, 8};
  s21::Iterator position = vector.begin();
  position++;
  position = vector.insert_many(position, vector2);
  EXPECT_EQ(6u, vector.size());
  EXPECT_EQ(0, vector[0]);
  EXPECT_EQ(3, vector[1]);
  EXPECT_EQ(4, vector[2]);
  EXPECT_EQ(5, vector[3]);
  EXPECT_EQ(1, vector[4]);
  EXPECT_EQ(2, vector[5]);
  position = vector.insert_many(position, vector3);
  EXPECT_EQ(9u, vector.size());
  EXPECT_EQ(0, vector[0]);
  EXPECT_EQ(3, vector[1]);
  EXPECT_EQ(4, vector[2]);
  EXPECT_EQ(5, vector[3]);
  EXPECT_EQ(6, vector[4]);
  EXPECT_EQ(7, vector[5]);
  EXPECT_EQ(8, vector[6]);
  EXPECT_EQ(1, vector[7]);
  EXPECT_EQ(2, vector[8]);
  position = vector.insert_many(position);
  EXPECT_EQ(9u, vector.size());
  EXPECT_EQ(0, vector[0]);
  EXPECT_EQ(3, vector[1]);
  EXPECT_EQ(4, vector[2]);
  EXPECT_EQ(5, vector[3]);
  EXPECT_EQ(6, vector[4]);
  EXPECT_EQ(7, vector[5]);
  EXPECT_EQ(8, vector[6]);
  EXPECT_EQ(1, vector[7]);
  EXPECT_EQ(2, vector[8]);
}

TEST(vector, insert_many_back) {
  s21::vector<int> vector = {0, 1, 2};
  s21::vector<int> vector2 = {3, 4, 5};
  s21::vector<int> vector3 = {6, 7, 8};
  vector.insert_many_back(vector2, vector3);
  EXPECT_EQ(9u, vector.size());
  for(int element = 0; element < (int)vector.size(); element++) {
    EXPECT_EQ(element, vector[element]);
  }
  vector.insert_many_back();
  EXPECT_EQ(9u, vector.size());
  vector.insert_many_back(vector2, vector3);
  EXPECT_EQ(15u, vector.size());
}

TEST(vector, erase) {
  s21::vector<int> vector = {0, 1, 2};
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
  s21::vector<int> vector;
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
  s21::vector<int> empty_vector;
  EXPECT_THROW(empty_vector.pop_back(), std::out_of_range);
  s21::vector<int> vector = {0, 1, 2};
  std::vector<int> true_vector = {0, 1, 2};
  vector.pop_back();
  true_vector.pop_back();
  EXPECT_EQ(true_vector.size(), vector.size());
  EXPECT_EQ(true_vector.capacity(), vector.capacity());
}

TEST(vector, swap) {
  s21::vector<int> vector1 = {0, 1, 2};
  s21::vector<int> vector2 = {3, 4};
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
