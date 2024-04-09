#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <initializer_list>
#include <numeric>

namespace s21 {

template <class T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;
  using size_type = size_t;

 private:
  struct node {
    value_type value;
    node *next;
    node *prev;

    node(const_reference value_input) {
      value = value_type(value_input);
      next = nullptr;
      prev = nullptr;
    }
    // node(value_type&& value) {
    //     this->value = value_type(value);
    // }
    node(const_reference value_input, node *next_input, node *prev_input) {
      value = value_input;
      next = next_input;
      prev = prev_input;
    }
  };

  node *head;
  node *tail;
  // node fake_node;
  size_type size_;

 public:
  class iterator {
   public:
    iterator() = delete;

    iterator(node *ptr) { this->ptr = ptr; }

    iterator(iterator &other) { this->ptr = other.ptr; }

    ~iterator() = default;

    iterator &operator=(const iterator &other) {
      this->ptr = other.ptr;
      return *this;
    }

    bool operator==(iterator &other) const { return this->ptr == other.ptr; }

    bool operator!=(iterator &other) const { return this->ptr != other.ptr; }

    bool operator!=(std::nullptr_t) const { return this->ptr != nullptr; }

    iterator &operator++() {
      ptr = ptr->next;
      return *this;
    }

    iterator operator++(int) {
      // for (int i = 0; i < count; i++) {
      //     this++;
      // }
      // return this;
      auto temp = list<value_type>::iterator(*this);
      ++(*this);
      return temp;
    }

    iterator &operator--() {
      ptr = ptr->prev;
      return *this;
    }

    // iterator operator--(int) {
    //     auto temp = list<value_type>::iterator(*this);
    //     --(*this);
    //     return temp;
    // }

    reference operator*() const { return ptr->value; }

    pointer operator->() const { return &(ptr->value); }

    node *node_next_pointer() const { return ptr->next; }

    node *node_prev_pointer() const { return ptr->prev; }

    node *node_pointer() { return ptr; }

   private:
    node *ptr;
  };

  // class const_iterator {
  // public:
  //     using value_type = value_type;
  //     using reference = const_reference;
  //     using pointer = const_pointer;
  //     using difference_type = difference_type;
  //     using iterator_type = std::bidirectional_iterator_tag;

  //     const_iterator() = delete;

  //     const_iterator(const node *ptr) {
  //         this->ptr = ptr;
  //     }

  //     const_iterator(const const_iterator &other) {
  //         this->ptr = other.ptr;
  //     }

  //     const_iterator(const iterator &other) {
  //         this->ptr = other.ptr;
  //     }

  //     ~const_iterator() = default;

  //     const_iterator &operator=(const const_iterator &other) {
  //         ptr = other.ptr;
  //         return *this;
  //     }

  //     bool operator==(const const_iterator &other) const {
  //         return this->ptr == other.ptr;
  //     }

  //     bool operator!=(const const_iterator &other) const {
  //         return this->ptr != other.ptr;
  //     }

  //     const_iterator &operator++() {
  //         ptr = ptr->next;
  //         if (ptr == &fake_node) {
  //             ptr = ptr->next;
  //         }
  //         return *this;
  //     }

  //     const_iterator operator++(int) {
  //         auto temp = list<value_type>::const_iterator(*this);
  //         ++(*this);
  //         return temp;
  //     }

  //     const_iterator &operator--() {
  //         ptr = ptr->prev;
  //         if (ptr == &fake_node) {
  //             ptr = ptr->prev;
  //         }
  //         return *this;
  //     }

  //     const_iterator operator--(int) {
  //         auto temp = list<value_type>::const_iterator(*this);
  //         --(*this);
  //         return temp;
  //     }

  //     reference operator*() const {
  //         return ptr->value;
  //     }

  //     pointer operator->() const {
  //         return &(ptr->value);
  //     }
  // private:
  //     node *ptr;
  // };

  // using reverse_iterator = std::reverse_iterator<iterator>;
  // using const_reverse_iterator = std::const_reverse_iterator<const_iterator>;

  // list() noexcept : size_(0), head(nullptr), tail(nullptr) {}

  list() {
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
  }

  list(size_type n) : head(nullptr), tail(nullptr), size_(0u) {
    for (size_type i = 0u; i < n; i++) {
      this->push_back(T());
    }
  }

  list(std::initializer_list<value_type> const &items) {
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
    for (auto item = items.begin(); item != items.end(); item++) {
      this->push_back(*item);
    }
  }

  list(const list &l) : head(nullptr), tail(nullptr), size_(0u) {
    node *current = l.head;
    while (current != nullptr) {
      this->push_back(current->value);
      current = current->next;
    }
  }

  list(list &&l) : head(l.head), tail(l.tail), size_(l.size()) {
    l.head = nullptr;
    l.tail = nullptr;
    l.size_ = 0u;
  }

  ~list() {
    if (!empty() || head != nullptr) {
      for (node *element = this->head;;) {
        node *next_node = element->next;
        delete element;
        element = next_node;
        if (element->next == nullptr) {
          delete element;
          break;
        }
      }
      //     std::cout << "Here2" << std::endl;
    }
    size_ = 0u;
    head = nullptr;
    tail = nullptr;
  }

  list &operator=(list &&l) {
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
    this = std::copy(l);
    return this;
  }

  // explicit list(size_type count) : list() {
  //     value_type val = value_type();
  //     for (size_type i = 0; i < count; ++i) {
  //         push_back(val);
  //     }
  // }

  // explicit list(size_type count, const_reference value) : list() {
  //     for (size_type i = 0; i < count; ++i) {
  //         push_back(value);
  //     }
  // }

  // list(const list &other) : list() {
  //     for (auto it = other.begin(); it != other.end(); ++it) {
  //         push_back(*it);
  //     }
  // }

  // list(list &&other) : list() {
  //     for (auto it = other.begin(); it != other.end(); ++it) {
  //         push_back(std::move(*it));
  //     }
  // }

  // list(std::initializer_list<value_type> init_list) : list() {
  //     for (auto it = init_list.begin(); it != init_list.end(); ++it) {
  //         push_back(*it);
  //     }
  // }

  // list &operator=(const list&other) {

  //     for (auto it = other.begin(); it != other.end(); ++it) {

  //     }
  // }

  // list &operator=(list&& other) {
  //     size_ = other._size;
  //     head = other.head;
  //     tail = other.tail;
  //     fake_node = other.fake_node;
  //     head->prev = &fake_node;
  //     tail->next = &fake_node;
  //     other.size_ = 0;
  //     other.head = nullptr;
  //     other.tail = nullptr;
  //     other.fake_node.next = nullptr;
  //     other.fake_node.prev = nullptr;
  // }

  reference front() { return head->value; }

  // inline const_reference front() const {
  //     return head->value;
  // }

  reference back() { return tail->value; }

  // inline const_reference back() const {
  //     return tail->value;
  // }

  iterator begin() { return iterator(this->head); }

  // inline const_iterator begin() const {
  //     return const_iterator(head);
  // }

  // inline const_iterator cbegin() const {
  //     return const_iterator(head);
  // }

  iterator end() { return iterator(this->tail); }

  // inline const_iterator end() const {
  //     return const_iterator(&fake_node);
  // }

  // inline const_iterator cend() const {
  //     return const_iterator(&fake_node);
  // }

  // inline reverse_iterator rbegin() {
  //     return reverse_iterator(tail);
  // }

  // inline const_reverse_iterator rbegin() const {
  //     return const_reverse_iterator(tail);
  // }

  // inline const_reverse_iterator crbegin() const {
  //     return const_reverse_iterator(tail);
  // }

  // inline reverse_iterator rend() {
  //     return reverse_iterator(&fake_node);
  // }

  // inline const_reverse_iterator rend() const {
  //     return const_reverse_iterator(&fake_node);
  // }

  // inline const_reverse_iterator crend() const {
  //     return const_reverse_iterator(&fake_node);
  // }

  inline size_type size() const noexcept { return size_; }

  size_type max_size() const {
    return std::numeric_limits<size_t>::max() / sizeof(node(value_type));
  }

  bool empty() const noexcept { return size_ == 0; }

  void clear() { this->~list(); }

  iterator insert(iterator pos, const_reference value) {
    node *new_node =
        new node(value, pos.node_next_pointer(), pos.node_pointer());
    pos.node_pointer()->next = new_node;
    ++pos;
    if (pos.node_next_pointer() != nullptr) {
      pos.node_next_pointer()->prev = new_node;
      // ++pos;
      // pos.node_pointer()->prev = new_node;
      // --pos;
    }
    return pos;
  }

  void erase(iterator pos) {
    pos.node_prev_pointer()->next = pos.node_next_pointer();
    pos.node_next_pointer()->prev = pos.node_prev_pointer();
    delete pos.node_pointer();
  }

  // void resize(size_type newsize_) {
  //     if (size_ == new_size) return;
  //     if ()
  // }

  // void resize(size_type newsize_, const_reference value);

  void push_back(const_reference value) {
    node *new_node = new node(value);
    if (empty()) {
      head = new_node;
      tail = new_node;
    } else {
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }
    tail->next = nullptr;
    ++size_;
  }

  // void push_back(value_type&& value) {
  //     node *new_node = new node(value);
  //     if (empty()) {
  //         head = new_node;
  //         tail = new_node;
  //         head->prev = &fake_node;
  //         fake_node.next = head;
  //     } else {
  //         tail->next = new_node;
  //         new_node->prev = tail;
  //         tail = new_node;
  //     }
  //     tail->next = &fake_node;
  //     fake_node.prev = tail;
  //     ++size_;
  // }

  void push_front(const_reference value) {
    node *new_node = new node(value);
    if (empty()) {
      head = new_node;
      tail = new_node;
    } else {
      head->prev = new_node;
      new_node->next = head;
      head = new_node;
    }
    head->prev = nullptr;
    ++size_;
  }

  // void push_front(value_type&& value) {
  //     node *new_node = new node(value);
  //     if (empty()) {
  //         head = new_node;
  //         tail = new_node;
  //         tail->next = &fake_node;
  //         fake_node.prev = tail;
  //     } else {
  //         head->prev = new_node;
  //         new_node->next = head;
  //         head = new_node;
  //     }
  //     head->prev = &fake_node;
  //     fake_node.next = head;
  //     ++size_;
  // }
  void head_modifier(node *input) { this->head = input; }

  void tail_modifier(node *input) { this->tail = input; }

  void pop_back() {
    if (size_ == 0) return;
    if (size_ == 1) {
      delete tail;
      head = nullptr;
      tail = nullptr;
    } else {
      node *prev = tail->prev;
      delete tail;
      tail = prev;
      tail->next = nullptr;
    }
    size_--;
  }

  void pop_front() {
    if (size_ == 0) return;
    if (size_ == 1) {
      delete head;
      head = nullptr;
      tail = nullptr;
    } else {
      node *next = head->next;
      delete head;
      head = next;
      head->prev = nullptr;
    }
    size_--;
  }

  void swap(list &other) {
    node *other_head = other.begin().node_pointer();
    node *other_tail = other.end().node_pointer();
    other.head_modifier(this->head);
    other.tail_modifier(this->tail);
    head = other_head;
    tail = other_tail;
  }

  void merge(list &other) {
    for (iterator iter = other.begin(); iter != nullptr; ++iter) {
      this->push_back(iter.node_pointer()->value);
    }
  }

  void splice(iterator pos, list &other) {
    for (iterator iter = other.begin(); iter != nullptr; ++iter) {
      pos = this->insert(pos, iter.node_pointer()->value);
    }
  }

  void reverse() {
    node *current = head;
    node *prev = nullptr;
    node *next = nullptr;

    while (current != nullptr) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }
    head = prev;
  }

  void unique() {
    node *current = head;
    node *prev_unique = nullptr;

    while (current != nullptr) {
      if (prev_unique && current->value == prev_unique->value) {
        erase(iterator(current));
        current = prev_unique;
      } else {
        prev_unique = current;
      }
      current = current->next;
    }
  }

  void sort() {
    bool swapped = true;
    while (swapped) {
      swapped = false;
      node *current = head;
      while (current->next != nullptr) {
        if (current->value > current->next->value) {
          int temp = current->value;
          current->value = current->next->value;
          current->next->value = temp;
          swapped = true;
        }
        current = current->next;
      }
    }
  }

  void printAll() {
    for (node *current = head; current != nullptr;) {
      std::cout << current->value << std::endl;
      current = current->next;
    }
  }

  // void remove(const_reference value) {
  //     for (auto it = )
  // }
};

}  // namespace s21

#endif  // S21_LIST_H_
