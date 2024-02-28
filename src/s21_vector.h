#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
// #include <initializer_list>
// #include <utility>

namespace s21
{

template<typename Vector>
class Iterator {
 public:
  using value_type = typename Vector::value_type;
  using iterator = value_type *;
  using reference = value_type &;
 public:
  Iterator(iterator ptr) {
    ptr_ = ptr; 
  }

  Iterator& operator++() {
    ptr_++;
    return *this;
  }
  
  Iterator operator++(int) {
    Iterator iter = *this;
    ++(*this);
    return iter;
  }

  Iterator& operator--() {
    ptr_--;
    return *this;
  }
  
  Iterator operator--(int) {
    Iterator iter = *this;
    --(*this);
    return iter;
  }

  reference operator[](int index) {
    return *(ptr_[index]);
  }

  iterator operator->() {
    return ptr_;
  }

  reference operator*() {
    return *ptr_;
  }

  iterator operator+(int value) {
    return ptr_ + value;
  }

  iterator operator-(int value) {
    return ptr_ - value;
  }

  bool operator==(const Iterator& other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const Iterator& other) const {
    return ptr_ != other.ptr_;
  }

  iterator get_ptr() {
    return ptr_;
  }

 private:
  iterator ptr_;
};

template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  // using iterator = T *;
  using iterator = Iterator<Vector<value_type>>;
  // using const_iterator = const T *;
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

  Vector& operator=(Vector &&vector) {
    this->~Vector();
    size_ = vector.size_;
    capacity_ = vector.capacity_;
    if (size_ > 0) {
      value_type *copy_data = new value_type[capacity_];
      for (size_type element = 0; element < size_; element++) {
        copy_data[element] = vector.data_[element];
      }
      data_ = copy_data;
    } else {
      data_ = vector.data_;
    }
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

  iterator begin() {
    return iterator(data_);
  }

  iterator end() {
    return iterator(data_ + size_);
  }

  bool empty() const {
    return capacity_ > 0 && size_ > 0 ? false : true;
  }

  size_type size() const {
    return size_;
  }

  size_type max_size() const {
    return std::numeric_limits<size_t>::max() / sizeof(value_type);
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

  void shrink_to_fit() {
    if (size_ < capacity_ && data_) {
      value_type *shrink_data_capacity = new value_type[size_];
      for (size_type element = 0; element < size_ ; element++) {
        shrink_data_capacity[element] = data_[element];
      }
      delete[] data_;
      data_ = shrink_data_capacity;
      capacity_ = size_;
    }
  }

  void clear() {
    if (data_) {
      value_type *shrink_data_capacity = new value_type[capacity_];
      delete[] data_;
      data_ = shrink_data_capacity;
      size_ = 0;
    }

  }

  iterator insert(iterator pos, const_reference value) {
    int position_difference = this->end().get_ptr() - pos.get_ptr();
    size_++;
    if (size_ >= capacity_) {
      if (capacity_ == 0) reserve(1);
      else reserve(capacity_ * 2);
    }
    for (iterator iter = this->end(); iter != this->end() - position_difference - 1; iter--) {
      *iter = *(iter - 1);
    }
    pos = this->end() - position_difference - 1;
    *pos = value;
    return pos;
  }

  void erase(iterator pos) {
    for (iterator iter = pos; iter != this->end() - 1; iter++) {
      *iter = *(iter + 1);
    }
    size_--;
  }

  void push_back(const value_type value) {
    if (size_ >= capacity_) {
      if (capacity_ == 0) reserve(1);
      else reserve(capacity_ * 2);
    }
    data_[size_] = value;
    size_++;
  }

  void pop_back() {
    size_--;
  }

  void swap(Vector& other) {
    size_type buff_size = other.size();
    size_type buff_capacity = other.capacity();
    value_type *buff_data = other.data();

    other.data_ = this->data_;
    other.size_ = this->size_;
    other.capacity_ = this->capacity_;

    data_ = buff_data;
    size_ = buff_size;
    capacity_ = buff_capacity;
  }

 private:
  size_type size_ = 0u;
  size_type capacity_ = 0u;
  value_type *data_ = nullptr;

};
  
} // namespace s21

#endif
