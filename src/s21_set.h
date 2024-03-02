#ifndef S21_SET_H
#define S21_SET_H

#include <iostream>
#include <limits>

namespace s21 {
template <class T>
class Set {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

 protected:
  struct Node {
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    Node* parent_ = nullptr;
    value_type data_;

    Node(const value_type data) : data_(data){};
    ~Node() {
      if (left_ != nullptr) {
        delete left_;
        left_ = nullptr;
      }
      if (right_ != nullptr) {
        delete right_;
        right_ = nullptr;
      }
    }
  };

 private:
  Node* root_;
  size_type nodeCount_;

 public:
  template <class value_type>
  class Iterator {
   private:
    Node* current_;
    Node* successor_;

   public:
    Iterator(Node* node) : current_(node), successor_(nullptr) {}

    Iterator operator++() {
      if (current_->right_ != nullptr) {
        current_ = current_->right_;
        while (current_->left_ != nullptr) {
          current_ = current_->left_;
        }
      } else {
        successor_ = current_->parent_;
        while (current_->parent_ != nullptr &&
               current_ == current_->parent_->right_) {
          current_ = successor_;
          successor_ = successor_->parent_;
        }
        current_ = successor_;
      }
      return *this;
    }

    template <class L>
    bool operator!=(const L& other) const {
      return (current_ != other.getCurrent());
    }

    value_type operator*() const {
      if (current_ == nullptr)
        throw std::invalid_argument("Null pointer dereference");
      return current_->data_;
    }

    Node* getCurrent() const { return current_; }
  };

  template <class value_type>
  class ConstIterator {
   private:
    Node* current_;
    Node* successor_;

   public:
    ConstIterator(Node* node) : current_(node), successor_(nullptr) {}

    ConstIterator operator++() {
      if (current_->right_ != nullptr) {
        current_ = current_->right_;
        while (current_->left_ != nullptr) {
          current_ = current_->left_;
        }
      } else {
        successor_ = current_->parent_;
        while (current_->parent_ != nullptr &&
               current_ == current_->parent_->right_) {
          current_ = successor_;
          successor_ = successor_->parent_;
        }
        current_ = successor_;
      }
      return *this;
    }

    template <class L>
    bool operator!=(const L& other) const {
      return (current_ != other.getCurrent());
    }

    value_type operator*() const {
      if (current_ == nullptr)
        throw std::invalid_argument("Null pointer dereference");
      return current_->data_;
    }

    Node* getCurrent() const { return current_; }
  };

  using iterator = Iterator<T>;
  using const_iterator = ConstIterator<T>;

  Set() : root_(nullptr), nodeCount_(0) {}

  Set(std::initializer_list<value_type> const& items)
      : root_(nullptr), nodeCount_(0) {
    for (auto i : items) {
      insert(i);
    }
  }

  Set(const Set& copySet) : root_(nullptr), nodeCount_(0) {
    if (copySet.root_ != nullptr) {
      root_ = new Node(copySet.root_->data_);
      nodeCount_++;
      copyNodes(copySet.root_, root_);
    }
  }

  void copyNodes(Node* source, Node* destination) {
    if (source->left_ != nullptr) {
      destination->left_ = new Node(source->left_->data_);
      destination->left_->parent_ = destination;
      nodeCount_++;
      copyNodes(source->left_, destination->left_);
    }
    if (source->right_ != nullptr) {
      destination->right_ = new Node(source->right_->data_);
      destination->right_->parent_ = destination;
      nodeCount_++;
      copyNodes(source->right_, destination->right_);
    }
  }

  Set(Set&& moveSet) : root_(moveSet.root_), nodeCount_(moveSet.nodeCount_) {
    moveSet.root_ = nullptr;
    moveSet.nodeCount_ = 0;
  }

  ~Set() {
    root_ = nullptr;
    nodeCount_ = 0;
  };

  Set& operator=(Set&& s) {
    Set ptr = s;
    if (this != s) {
      clear();
      root_ = ptr.root_;
      ptr->root_ = nullptr;
    }
    return *this;
  }

  bool operator==(const Set& other) const {
    bool ret = true;
    if (size() != other.size())
      ret = false;
    else
      for (const_iterator it = cbegin(), ot = other.cbegin();
           it != cend() && ot != other.cend() && ret;) {
        if (*it != *ot) ret = false;
        ++it;
        ++ot;
      }
    return ret;
  }

  iterator begin() {
    Node* cur = root_;
    if (cur != nullptr)
      while (cur->left_) {
        cur = cur->left_;
      }
    return cur;
  }

  const_iterator cbegin() const {
    Node* cur = root_;
    if (cur != nullptr)
      while (cur->left_) {
        cur = cur->left_;
      }
    return cur;
  }

  iterator end() const {
    Node* cur = root_;
    if (cur != nullptr) {
      while (cur->right_) {
        cur = cur->right_;
      }
      cur = cur->right_;
    }
    return cur;
  }

  const_iterator cend() const {
    Node* cur = root_;
    if (cur != nullptr) {
      while (cur->right_) {
        cur = cur->right_;
      }
      cur = cur->right_;
    }
    return cur;
  }

  bool empty() const { return (nodeCount_ == 0); }

  size_type size() const { return nodeCount_; }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void clear() {
    if (root_ != nullptr) {
      delete root_;
      root_ = nullptr;
    }
    nodeCount_ = 0;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    bool add = true;
    bool makeroot = false;
    Node* newNode = new Node(value);
    if (root_ == nullptr) {
      root_ = newNode;
      makeroot = true;
    } else {
      Node* cur = root_;
      bool looking = true;
      while (looking) {
        if (value < cur->data_) {
          if (cur->left_ == nullptr) {
            cur->left_ = newNode;
            newNode->parent_ = cur;
            looking = false;
          } else {
            cur = cur->left_;
          }
        } else if (value > cur->data_) {
          if (cur->right_ == nullptr) {
            cur->right_ = newNode;
            newNode->parent_ = cur;
            looking = false;
          } else {
            cur = cur->right_;
          }
        } else {
          add = false;
          looking = false;
          delete newNode;
        }
      }
    }
    if (add) nodeCount_++;
    if (!add && makeroot) root_ = nullptr;
    return std::make_pair(newNode, add);
  }

  void erase(iterator pos) {
    if (pos.getCurrent() == root_) {
      Node* temp = root_;
      root_ = root_->left_;
      delete temp;
      nodeCount_--;
    } else {
      Node* cur = root_;
      while (cur != nullptr) {
        if (pos.getCurrent() == cur->left_) {
          Node* temp = cur->left_;
          cur->left_ = cur->left_->right_;
          delete temp;
          nodeCount_--;
          break;
        } else if (pos.getCurrent() == cur->right_) {
          Node* temp = cur->right_;
          cur->right_ = cur->right_->left_;
          delete temp;
          nodeCount_--;
          break;
        }
        cur = cur->left_;
      }
    }
  }

  void swap(Set& other) {
    Node* temp = this->root_;
    this->root_ = other.root_;
    other.root_ = temp;
    int othNodes = other.nodeCount_;
    other.nodeCount_ = nodeCount_;
    nodeCount_ = othNodes;
  }

  void merge(Set& other) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(it.getCurrent()->data_);
    }
  }

  iterator find(const value_type& key) {
    iterator ret = end();
    for (iterator it = begin(); it != end(); ++it) {
      if (*it == key) {
        ret = it;
        break;
      }
    }
    if (ret.getCurrent() == nullptr) throw std::out_of_range("Can't find key");
    return ret;
  }

  bool contains(const value_type& key) {
    bool ret = false;
    for (iterator it = begin(); it != end(); ++it) {
      if (*it == key) {
        ret = true;
        break;
      }
    }
    return ret;
  }

  void printAll() const {
    if (!empty()) {
      for (const_iterator it = cbegin();
           it.getCurrent() != nullptr && it != cend(); ++it) {
        std::cout << *it << " ";
      }
      std::cout << std::endl;
    } else {
      std::cout << "No elements in set" << std::endl;
    }
  }
};
}  // namespace s21

#endif