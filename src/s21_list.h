#ifndef S21_LIST_H
#define S21_LIST_H

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
        node(value_type value, node *next, node *prev);
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
        iterator(const node &*nod)
        iterator(const iterator &iter);
        ~iterator() = default;

        iterator &operator=(const iterator &iter);
        bool operator==(const iterator &iter) const;
        bool operator!=(const iterator &iter) const;

        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);

        reference operator*() const;
        pointer operator->() const;
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
        const_iterator(const const_iterator &iter);
        const_iterator(const iterator &iter);
        ~const_iterator() = default;

        const_iterator &operator=(const const_iterator &iter);
        bool operator==(const const_iterator &iter) const;
        bool operator!=(const const_iterator &iter) const;

        const_iterator &operator++();
        const_iterator operator++(int);
        const_iterator &operator--();
        const_iterator operator--(int);

        reference operator*() const;
        pointer operator->() const;
    private:
        node *ptr;
    };

    using reverse_iterator = std::reverse_iterator<iterator>
    using const_reverse_iterator = std::reverse_iterator<const_iterator>

    list() noexcept;
    explicit list(size_type count);
    list(size_type count, const_reference value);
    list(const list &right);
    list(list &&right);
    list(std::initializer_list<value_type> init_list);
    template <class InputIterator>
    list(InputIterator first, InputIterator last);

    void assign(size_type count, const_reference value);
    void assign(std::initializer_list<value_type> init_list);
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last);

    reference back();
    const_reference back() const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;

    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;
};

} // namespace s21

#include "s21_list.inl"

#endif 
