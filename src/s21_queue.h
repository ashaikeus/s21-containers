#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

namespace s21 {

template <class T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // constructor
  queue() : size_{0}, head_{nullptr}, end_{nullptr} {}

  queue(std::initializer_list<value_type> const &items)
      : size_{0}, head_{nullptr}, end_{nullptr} {
    for (const auto &i : items) push(i);
  }
  queue(const queue<T> &q) : size_{0}, head_{nullptr}, end_{nullptr} {
    Node *current = q.head_;
    while (current != nullptr) {
      push(current->info_);
      current = current->value_;
    }
  }

  queue(queue<T> &&q) : size_{q.size_}, head_{q.head_}, end_{q.end_} {
    q.size_ = 0;
    q.head_ = nullptr;
    q.end_ = nullptr;
  }

  ~queue() { clear(); }

  queue &operator=(const queue &q) {
    if (this != &q) {
      clear();
      queue tmp(q);
      swap(tmp);
    }
    return *this;
  }

  queue &operator=(queue &&q) {
    if (this != &q) {
      clear();
      queue tmp(std::move(q));
      swap(tmp);
    }
    return *this;
  }

  bool empty() const { return head_ == nullptr; }

  size_type size() { return size_; }

  const_reference front() const {
    if (empty()) {
      throw "Queue is empty";
    }
    return head_->info_;
  }

  const_reference back() const {
    if (empty()) {
      throw "Queue is empty";
    }
    return end_->info_;
  }

  void push(const_reference value) {
    Node *newNode;
    newNode = new Node;
    newNode->info_ = value;
    newNode->value_ = nullptr;
    if (end_ == nullptr) {
      end_ = newNode;
      head_ = newNode;
    } else {
      end_->value_ = newNode;
      end_ = newNode;
    }
    ++size_;
  }
  void pop() {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    if (size_ != 0) {
      Node *tmp = head_;
      head_ = head_->value_;
      delete tmp;
      --size_;
    }
  }

  void clear() {
    while (!empty()) {
      pop();
    }
  }

  void swap(queue &q) {
    std::swap(size_, q.size_);
    std::swap(head_, q.head_);
    std::swap(end_, q.end_);
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (auto i : {std::forward<Args>(args)...}) {
      push(i);
    }
  }

 private:
  struct Node {
    T info_;
    Node *value_;
    Node() : info_(), value_(nullptr) {}
    Node(const value_type &value) : info_(value), value_(nullptr) {}
  };

  size_type size_;
  Node *head_;
  Node *end_;
};

}  // namespace s21

#endif  // S21_QUEUE_H_