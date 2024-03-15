#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include "s21_containers.h"

namespace s21 {

template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // constructor
  array() : arr_() {}
  // initializer list constructor
  array(std::initializer_list<value_type> const &items) {
    if (items.size() > N)
      throw std::invalid_argument("too many initializer values");

    size_type i = 0;
    for (auto it = items.begin(); i < items.size(); ++i, ++it) arr_[i] = *it;
    init_array(i, N, value_type{});
  }
  // copy constructor
  array(const array &a) {
    for (size_type i = 0; i < N; ++i) {
      arr_[i] = a.arr_[i];
    }
  }
  // move constructor
  array(array &&a) { std::move(a.cbegin(), a.cend(), arr_); }
  // destructor
  ~array() {}

  reference at(size_type pos) {
    if (pos >= N) throw std::invalid_argument("index is out of range");
    return arr_[pos];
  }

  array &operator=(const array &a) {
    std::copy(a.cbegin(), a.cend(), arr_);
    return *this;
  }

  reference operator[](size_type pos) { return arr_[pos]; }

  const_reference front() const { return arr_[0]; }
  const_reference back() const { return arr_[N - 1]; }

  iterator data() { return arr_; }

  iterator begin() { return arr_; }
  const_iterator cbegin() const { return arr_; }

  iterator end() { return arr_ + N; }
  const_iterator cend() const { return arr_ + N; }

  bool empty() const { return N == 0; }
  size_type size() const { return N; }
  size_type max_size() const { return N; }

  void swap(array &other) { std::swap(arr_, other.arr_); }
  void fill(const_reference value) { init_array(0, N, value); }

 private:
  T arr_[N];

  void init_array(size_type start_index, size_type end_index,
                  const_reference value) {
    for (size_type i = start_index; i < end_index; ++i) arr_[i] = value;
  }
};

template <typename T>
class array<T, 0> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  reference at(size_type) {
    throw std::out_of_range("Index out of array range");
  }

  const_reference front() const {
    throw std::invalid_argument("Array is empty");
  }

  const_reference back() const {
    throw std::invalid_argument("Array is empty");
  }

  iterator data() noexcept { return nullptr; }

  iterator begin() noexcept { return nullptr; }

  iterator end() noexcept { return nullptr; }

  size_type size() const noexcept { return 0; }

  size_type max_size() const noexcept { return 0; }

  bool empty() const noexcept { return true; }

  void swap(array &) noexcept {}

  void fill(const_reference) {}
};
}  // namespace s21
#endif  // SRC_S21_ARRAY_H_