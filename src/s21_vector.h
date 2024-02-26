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
    data_ = copy_vector.data_;
  }

  Vector(Vector &&move_vector) {
    size_ = move_vector.size_;
    capacity_ = move_vector.capacity_;
    data_ = move_vector.data_;

    move_vector.data_ = nullptr;
    move_vector.size_ = 0u;
    move_vector.capacity_ = 0u;
  }

  ~Vector() { delete[] data_; }

  size_type size() {
    return size_;
  }

  size_type capacity() {
    return capacity_;
  }

  const value_type *get_data_pointer() {
    return data_;
  }

  value_type at(size_type i);

  void push_back(value_type value);

 private:
  size_type size_;
  size_type capacity_;
  value_type *data_;

  void reserve_more_capacity(size_type new_capacity);
};

// template <class T>
// void Vector<T>::reserve_more_capacity(size_type new_capacity)
// {
//     if (new_capacity > capacity_)
//     {
//         value_type *buff = new value_type[new_capacity];
//         for (size_t i = 0; i < size_; ++i)
//             buff[i] = std::move(data_[i]);
//         delete[] data_;
//         data_ = buff;
//         capacity_ = new_capacity;
//     }
// }

// template <typename T>
// T Vector<T>::at(size_type i)
// {
//     return data_[i];
// }

// template <typename T>
// void Vector<T>::push_back(T value)
// {
//     if (size_ == capacity_)
//     {
//         reserve_more_capacity(size_ * 2);
//     }
//     data_[size_++] = value;
// }

#endif
