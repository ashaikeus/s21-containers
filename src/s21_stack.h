#ifndef S21_STACK_H_
#define S21_STACK_H_

namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() noexcept {
    size_ = 0u;
    capacity_ = 0u;
    data_ = nullptr;
  }

  stack(std::initializer_list<value_type> const &items) {
    size_ = items.size();
    capacity_ = items.size();
    data_ = new value_type[items.size()];

    int element = 0;
    for (auto item = items.begin(); item != items.end(); item++, element++) {
      data_[element] = *item;
    }
  }

  stack(const stack &copy_stack) {
    size_ = copy_stack.size_;
    capacity_ = copy_stack.capacity_;
    if (size_ > 0) {
      value_type *copy_data = new value_type[capacity_];
      for (size_type element = 0; element < size_; element++) {
        copy_data[element] = copy_stack.data_[element];
      }
      data_ = copy_data;
    } else {
      data_ = copy_stack.data_;
    }
  }

  stack(stack &&move_stack) {
    size_ = move_stack.size_;
    capacity_ = move_stack.capacity_;
    data_ = move_stack.data_;

    move_stack.data_ = nullptr;
    move_stack.size_ = 0u;
    move_stack.capacity_ = 0u;
  }

  ~stack() {
    size_ = 0u;
    capacity_ = 0u;
    delete[] data_;
  }

  const_reference top() {
    return size_ > 0 ? data_[this->top_position()]
                     : throw std::out_of_range("std::out_of_range");
  }

  size_type size() const { return size_; }

  bool empty() const { return capacity_ > 0 && size_ > 0 ? false : true; }

  void push(const value_type value) {
    if (size_ >= capacity_) {
      if (capacity_ == 0)
        reserve(1);
      else
        reserve(capacity_ * 2);
    }
    data_[size_] = value;
    size_++;
  }

  void pop() {
    if (size_ > 0)
      size_--;
    else
      throw std::out_of_range("std::out_of_range");
  }

  void swap(stack &other) {
    size_type buff_size = other.size();
    size_type buff_capacity = other.capacity_;
    value_type *buff_data = other.data_;

    other.data_ = this->data_;
    other.size_ = this->size_;
    other.capacity_ = this->capacity_;

    data_ = buff_data;
    size_ = buff_size;
    capacity_ = buff_capacity;
  }

  template <class... Args>
  void insert_many_front(Args... stacks) {
    (
        [&] {
          for (size_type i = 0; i < stacks.size(); i++) {
            this->push(stacks.data_[i]);
          }
        }(),
        ...);
  }

 private:
  size_type size_ = 0u;
  size_type capacity_ = 0u;
  value_type *data_ = nullptr;

  int top_position() const { return size_ - 1; }

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
};

}  // namespace s21

#endif  // S21_STACK_H_