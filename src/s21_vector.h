#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
// #include <initializer_list>
// #include <utility>

template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector() {
    size_ = 0u;
    capacity_ = 0u;
    data_ = nullptr;
  }

  explicit Vector(size_type new_size) {
    size_ = new_size;
    capacity_ = new_size;
    if (new_size) {
      data_ = new value_type[new_size];
    } else {
      data_ = nullptr;
    }
  }

  Vector(std::initializer_list<value_type> const &items) {
    size_ = items.size();
    capacity_ = items.size();
    data_ = new value_type[items.size()];

    int element = 0;
    for (auto item = items.begin(); item != items.end(); item++, element++) {
      data_[element] = *item;
    }
  }

  Vector(const Vector &copy_vector) {
    size_ = copy_vector.size_;
    capacity_ = copy_vector.capacity_;
    if (size_ > 0) {
      value_type *copy_data = new value_type[capacity_];
      for (size_type element = 0; element < size_; element++) {
        copy_data[element] = copy_vector.data_[element];
      }
      data_ = copy_data;
    } else {
      data_ = copy_vector.data_;
    }
  }

  Vector(Vector &&move_vector) {
    size_ = move_vector.size_;
    capacity_ = move_vector.capacity_;
    data_ = move_vector.data_;

    move_vector.data_ = nullptr;
    move_vector.size_ = 0u;
    move_vector.capacity_ = 0u;
  }

  ~Vector() {
    size_ = 0u;
    capacity_ = 0u;
    delete[] data_;
  }

  reference at(size_type index) {
    if (index < 0 || index >= size_) {
      throw std::out_of_range ("std::out_of_range");
    }
    return data_[index];
  }

  reference operator[](size_type index) {
    return data_[index];
  }

  const_reference operator[](size_type index) const {
    return data_[index];
  }

  const_reference front() {
    return data_[0];
  }

  const_reference back() {
    return data_[size_ - 1];
  }

  value_type *data() const {
    return data_;
  }

  bool empty() const {
    return capacity_ > 0 && size_ > 0 ? false : true;
  }

  size_type size() const {
    return size_;
  }

  size_type max_size() const {
    // return (unsigned long)pow(2, 64) / (unsigned long)sizeof(value_type);
    return std::numeric_limits<size_t>::max()/sizeof(value_type);
  }

  void reserve(size_type new_capacity) {
    if (new_capacity > capacity_) {
      value_type *larger_data_capacity = new value_type[new_capacity];
      for (size_type element = 0; element < size_ && data_; element++) {
        larger_data_capacity[element] = data_[element];
      }
      if (data_) delete[] data_;
      data_ = larger_data_capacity;
      capacity_ = new_capacity;
    }
  }

  size_type capacity() const {
    return capacity_;
  }

  void push_back(const value_type value) {
    if (size_ >= capacity_) {
      if (capacity_ == 0) reserve(1);
      else reserve(capacity_ * 2);
    }
    data_[size_] = value;
    size_++;
  }

 private:
  size_type size_ = 0u;
  size_type capacity_ = 0u;
  value_type *data_ = nullptr;

};

#endif
