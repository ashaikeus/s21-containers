#ifndef S21_MAP_H
#define S21_MAP_H

#include <iostream>

namespace s21 {
template <class Key, class T>
class Map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

 protected:
  struct Node {
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    Node* parent_ = nullptr;
    value_type data_;
    key_type key_;
    mapped_type value_;

    Node(value_type data)
        : data_(data), key_(data.first), value_(data.second){};

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

    Node* getCurrent() const { return current_; }

    bool operator==(std::nullptr_t) const { return current_ == nullptr; }
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

    Node* getCurrent() const { return current_; }

    bool operator==(std::nullptr_t) const { return current_ == nullptr; }
  };

  using iterator = Iterator<T>;
  using const_iterator = ConstIterator<T>;

  Map() : root_(nullptr), nodeCount_(0) {}

  Map(std::initializer_list<value_type> const& items)
      : root_(nullptr), nodeCount_(0) {
    for (auto i : items) {
      insert(i);
    }
  }

  Map(const Map& copyMap) : root_(nullptr), nodeCount_(0) {
    if (copyMap.root_ != nullptr) {
      root_ = new Node(copyMap.root_->data_);
      nodeCount_++;
      copyNodes(copyMap.root_, root_);
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

  Map(Map&& moveMap) : root_(moveMap.root_), nodeCount_(moveMap.nodeCount_) {
    moveMap.root_ = nullptr;
    moveMap.nodeCount_ = 0;
  }

  ~Map() {
    root_ = nullptr;
    nodeCount_ = 0;
  }

  Map& operator=(Map&& m) {
    Map ptr = m;
    if (this != m) {
      clear();
      root_ = ptr.root_;
      ptr->root_ = nullptr;
    }
    return *this;
  }

  bool operator==(const Map& other) const {
    bool ret = true;
    if (size() != other.size())
      ret = false;
    else
      for (const_iterator it = cbegin(), ot = other.cbegin();
           it != cend() && ot != other.cend() && ret;) {
        if ((it.getCurrent()->key_ != ot.getCurrent()->key_) ||
            (it.getCurrent()->value_ != ot.getCurrent()->value_))
          ret = false;
        ++it;
        ++ot;
      }
    return ret;
  }

  T& at(const Key& key) {
    if (!contains(key))
      throw std::out_of_range("Can't find element with given key");
    auto it = find(key);
    return it.getCurrent()->value_;
  }

  T& operator[](const Key& key) {
    if (!contains(key)) insert(std::make_pair(key, T()));
    auto it = find(key);
    return it.getCurrent()->value_;
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
    key_type k = value.first;
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
        if (k < cur->key_) {
          if (cur->left_ == nullptr) {
            cur->left_ = newNode;
            newNode->parent_ = cur;
            looking = false;
          } else {
            cur = cur->left_;
          }
        } else if (k > cur->key_) {
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

  std::pair<iterator, bool> insert(const Key& key, const mapped_type& obj) {
    return insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key,
                                             const mapped_type& obj) {
    if (contains(key)) erase(find(key));
    return insert(key, obj);
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

  iterator find(const key_type& key) {
    // There's no such function in Map specification, but the standard library
    // has it (https://cplusplus.com/reference/map/map/find/) Besides, it makes
    // working with map's elements much easier
    iterator ret = end();
    for (iterator it = begin(); it != end(); ++it) {
      if (it.getCurrent()->key_ == key) {
        ret = it;
        break;
      }
    }
    if (ret.getCurrent() == nullptr) throw std::out_of_range("Can't find key");
    return ret;
  }

  void swap(Map& other) {
    Node* temp = this->root_;
    this->root_ = other.root_;
    other.root_ = temp;
    int othNodes = other.nodeCount_;
    other.nodeCount_ = nodeCount_;
    nodeCount_ = othNodes;
  }

  void merge(Map& other) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(it.getCurrent()->data_);
    }
  }

  bool contains(const Key& key) {
    bool ret = false;
    for (iterator it = begin(); it != end(); ++it) {
      if (it.getCurrent()->key_ == key) {
        ret = true;
        break;
      }
    }
    return ret;
  }

  // void printAll() const {
  //   if (!empty()) {
  //     for (const_iterator it = cbegin();
  //          it.getCurrent() != nullptr && it != cend(); ++it) {
  //       std::cout << "{" << it.getCurrent()->key_ << ", "
  //                 << it.getCurrent()->value_ << "}, ";
  //     }
  //     std::cout << std::endl;
  //   } else {
  //     std::cout << "No elements in set" << std::endl;
  //   }
  // }
};
}  // namespace s21

#endif
