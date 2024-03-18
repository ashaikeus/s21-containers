#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <initializer_list>

namespace s21 {

template <class T>
class list {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

private:
    struct node {
        value_type value;
        node *next;
        node *prev;
        node(const_reference value) {
            this->value = value_type(value);
        }
        node(value_type&& value) {
            this->value = value_type(value);
        }
    };

    node *head;
    node *tail;
    node fake_node;
    size_type _size;

public:
    class iterator {
    public:
        using value_type = value_type;
        using reference = reference;
        using pointer = pointer;
        using difference_type = difference_type;
        using iterator_type = std::bidirectional_iterator_tag;

        iterator() = delete;

        iterator(const node *ptr) {
            this->ptr = ptr;
        }
        iterator(const iterator &other) {
            this->ptr = other.ptr;
        }

        ~iterator() = default;

        iterator &operator=(const iterator &other) {
            this->ptr = other.ptr;
            return *this;
        }

        bool operator==(const iterator &other) const {
            return this->ptr == other.ptr;
        }

        bool operator!=(const iterator &other) const {
            return this->ptr != other.ptr;
        }

        iterator &operator++() {
            ptr = ptr->next;
            if (ptr == &fake_node) {
                ptr = ptr->next;
            }
            return *this;
        }

        iterator operator++(int) {
            auto temp = list<value_type>::iterator(*this);
            ++(*this);
            return temp;
        }

        iterator &operator--() {
            ptr = ptr->prev;
            if (ptr == &fake_node) {
                ptr = ptr->prev;
            }
            return *this;
        }

        iterator operator--(int) {
            auto temp = list<value_type>::iterator(*this);
            --(*this);
            return temp;
        }

        reference operator*() const {
            return ptr->value;
        }
        pointer operator->() const {
            return &(ptr->value);
        }
    private:
        node *ptr;
    };

    class const_iterator {
    public:
        using value_type = value_type;
        using reference = const_reference;
        using pointer = const_pointer;
        using difference_type = difference_type;
        using iterator_type = std::bidirectional_iterator_tag;

        const_iterator() = delete;

        const_iterator(const node *ptr) {
            this->ptr = ptr;
        }

        const_iterator(const const_iterator &other) {
            this->ptr = other.ptr;
        }

        const_iterator(const iterator &other) {
            this->ptr = other.ptr;
        }

        ~const_iterator() = default;

        const_iterator &operator=(const const_iterator &other) {
            ptr = other.ptr;
            return *this;
        }

        bool operator==(const const_iterator &other) const {
            return this->ptr == other.ptr;
        }

        bool operator!=(const const_iterator &other) const {
            return this->ptr != other.ptr;
        }

        const_iterator &operator++() {
            ptr = ptr->next;
            if (ptr == &fake_node) {
                ptr = ptr->next;
            }
            return *this;
        }

        const_iterator operator++(int) {
            auto temp = list<value_type>::const_iterator(*this);
            ++(*this);
            return temp;
        }

        const_iterator &operator--() {
            ptr = ptr->prev;
            if (ptr == &fake_node) {
                ptr = ptr->prev;
            }
            return *this;
        }

        const_iterator operator--(int) {
            auto temp = list<value_type>::const_iterator(*this);
            --(*this);
            return temp;
        }

        reference operator*() const {
            return ptr->value;
        }

        pointer operator->() const {
            return &(ptr->value);
        }
    private:
        node *ptr;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::const_reverse_iterator<const_iterator>;

    list() noexcept : _size(0), head(nullptr), tail(nullptr) {}

    explicit list(size_type count) : list() {
        value_type val = value_type();
        for (size_type i = 0; i < count; ++i) {
            push_back(val);
        }
    }

    explicit list(size_type count, const_reference value) : list() {
        for (size_type i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    list(const list &other) : list() {
        for (auto it = other.begin(); it != other.end(); ++it) {
            push_back(*it);
        }
    }

    list(list &&other) : list() {
        for (auto it = other.begin(); it != other.end(); ++it) {
            push_back(std::move(*it));
        }
    }

    list(std::initializer_list<value_type> init_list) : list() {
        for (auto it = init_list.begin(); it != init_list.end(); ++it) {
            push_back(*it);
        }
    }

    list &operator=(const list&other) {

        for (auto it = other.begin(); it != other.end(); ++it) {

        }
    }

    list &operator=(list&& other) {
        _size = other._size;
        head = other.head;
        tail = other.tail;
        fake_node = other.fake_node;
        head->prev = &fake_node;
        tail->next = &fake_node;
        other._size = 0;
        other.head = nullptr;
        other.tail = nullptr;
        other.fake_node.next = nullptr;
        other.fake_node.prev = nullptr;
    }

    inline reference front() {
        return head->value;
    }

    inline const_reference front() const {
        return head->value;
    }

    inline reference back() {
        return tail->value;
    }

    inline const_reference back() const {
        return tail->value;
    }

    inline iterator begin() {
        return iterator(head);
    }

    inline const_iterator begin() const {
        return const_iterator(head);
    }

    inline const_iterator cbegin() const {
        return const_iterator(head);
    }

    inline iterator end() {
        return iterator(&fake_node);
    }

    inline const_iterator end() const {
        return const_iterator(&fake_node);
    }

    inline const_iterator cend() const {
        return const_iterator(&fake_node);
    }

    inline reverse_iterator rbegin() {
        return reverse_iterator(tail);
    }

    inline const_reverse_iterator rbegin() const {
        return const_reverse_iterator(tail);
    }

    inline const_reverse_iterator crbegin() const {
        return const_reverse_iterator(tail);
    }

    inline reverse_iterator rend() {
        return reverse_iterator(&fake_node);
    }

    inline const_reverse_iterator rend() const {
        return const_reverse_iterator(&fake_node);
    }

    inline const_reverse_iterator crend() const {
        return const_reverse_iterator(&fake_node);
    }

    inline size_type size() const noexcept {
        return _size;
    }
    
    inline bool empty() const noexcept {
        return _size == 0;
    }

    void resize(size_type new_size) {
        if (_size == new_size) return;
        if ()
    }

    void resize(size_type new_size, const_reference value);

    iterator insert(const_iterator where, const_reference value);
    iterator insert(const_iterator where, value_type&& value);
    iterator insert(const_iterator where, size_type count, const_reference value);
    iterator insert(const_iterator where, std::initializer_list<value_type> init_list);

    template <class InputIterator>
    iterator insert(const_iterator where, InputIterator first, InputIterator last);

    iterator erase(const_iterator where) {

    }

    iterator erase(const_iterator first, const_iterator last) {
        
    }

    void push_back(const_reference value) {
        node *new_node = new node(value);
        if (empty()) {
            head = new_node;
            tail = new_node;
            tail->prev = &fake_node;
            fake_node.next = head;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        tail->next = &fake_node;
        fake_node.prev = tail;
        ++_size;
    }

    void push_back(value_type&& value) {
        node *new_node = new node(value);
        if (empty()) {
            head = new_node;
            tail = new_node;
            head->prev = &fake_node;
            fake_node.next = head;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        tail->next = &fake_node;
        fake_node.prev = tail;
        ++_size;
    }

    void push_front(const_reference value) {
        node *new_node = new node(value);
        if (empty()) {
            head = new_node;
            tail = new_node;
            tail->next = &fake_node;
            fake_node.prev = tail;
        } else {
            head->prev = new_node;
            new_node->next = head;
            head = new_node;
        }
        head->prev = &fake_node;
        fake_node.next = head;
        ++_size;
    }

    void push_front(value_type&& value) {
        node *new_node = new node(value);
        if (empty()) {
            head = new_node;
            tail = new_node;
            tail->next = &fake_node;
            fake_node.prev = tail;
        } else {
            head->prev = new_node;
            new_node->next = head;
            head = new_node;
        }
        head->prev = &fake_node;
        fake_node.next = head;
        ++_size;
    }

    void pop_back() {
        if (_size == 0) return;
        _size--;
        if (_size == 1) {
            delete tail;
            head = nullptr;
            tail = nullptr;
            fake_node.next = nullptr;
            fake_node.prev = nullptr;   
        } else {
            node *prev = tail->prev;
            delete tail;
            tail = prev;
            fake_node.prev = tail;
        }
    }

    void pop_front() {
        if (_size == 0) return;
        _size--;
        if (_size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            fake_node.next = nullptr;
            fake_node.prev = nullptr;   
        } else {
            node *next = head->next;
            delete head;
            head = next;
            fake_node.next = head;
        }
    }

    void remove(const_reference value) {
        for (auto it = )
    }
};

} // namespace s21

#endif // S21_LIST_H_
