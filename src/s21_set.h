#ifndef S21_SET_H
#define S21_SET_H

#include <iostream>

template <class T>
class Set {
   public:
    using key_type = T;
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;

   protected:
    struct Node {
        Node* left_ = nullptr;
        Node* right_ = nullptr;
        Node* parent_ = nullptr;
        value_type data_;
        bool visited_ = false;

        Node(const value_type data) : data_(data) {};
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

       public:
        Iterator(Node* node) : current_(node) {}

        Iterator operator++() {  // TO-DO duplicates (perhaps rewrite code logic)
            if (current_->right_ != nullptr && !current_->right_->visited_) {
                current_ = current_->right_;
            } else if (current_->left_ != nullptr && !current_->left_->visited_) {
                current_ = current_->left_;
            } else if (current_->parent_ != nullptr) {
                current_->visited_ = true;
                current_ = current_->parent_;
            } else {
                current_ = nullptr;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return (current_ != other.current_);
        }

        value_type operator*() {
            return current_->data_;
        }
    };
    using iterator = Iterator<T>;
    // using iterator = SetIterator<T>;
    // using const_iterator = SetConstIterator<T>;

    Set() : root_(nullptr), nodeCount_(0) {}

    Set(std::initializer_list<value_type> const &items) : root_(nullptr), nodeCount_(0) {
        for (auto i : items) {
            insert(i);
        }
    }

    Set(const Set &s);  // copy

    Set(Set &&s);  // move

    ~Set() {
        root_ = nullptr;
        nodeCount_ = 0;
    };

    // operator=(Set &&s);

    iterator begin() {
        Node* cur = root_;
        while (cur->left_) {
            cur = cur->left_;
        }
        return cur;
    }

    iterator end() {
        Node* cur = root_;
        while (cur->right_) {
            cur = cur->right_;
        }
        return cur->right_;
    }

    bool empty() {
        return (nodeCount_ == 0);
    }

    size_type size() {
        return nodeCount_;
    }

    size_type maxSize();

    void clear() {
        if (root_ != nullptr) {
            delete root_;
            root_ = nullptr;
            nodeCount_ = 0;
        }
    }

    std::pair<iterator, bool> insert(const value_type& value) {
        bool rBool = true;
        Node* newNode = new Node(value);
        if (root_ == nullptr && rBool) {
            root_ = newNode;
        } else if (rBool) {
            Node* cur = root_;
            bool go = true;
            while (go) {
                if (value < cur->data_) {
                    if (cur->left_ == nullptr) {
                        cur->left_ = newNode;
                        newNode->parent_ = cur;
                        go = false;
                    } else {
                        cur = cur->left_;
                    }
                } else if (value > cur->data_) {
                    if (cur->right_ == nullptr) {
                        cur->right_ = newNode;
                        newNode->parent_ = cur;
                        go = false;
                    } else {
                        cur = cur->right_;
                    }
                }
            }
        }
        nodeCount_ += rBool;
        return std::make_pair(newNode, rBool);
    }

    // void erase(iterator pos);
    void swap(Set& other);
    void merge(Set& other);

    // iterator find(const Key& key);
    // bool contains(const Key& key);

    void printAll() {
        // int i = 0;  // limiter
        for (iterator it = begin(); it != end(); ++it) {
            std::cout << *it << " ";
            // i++;
            // if (i > 20) break;
        }
        std::cout << std::endl;
    }
};

#endif