#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <utility>

namespace s21 {
template <class T>
class queue {
public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    queue() noexcept;
    queue(const queue &q);
    queue(queue &&q);
    queue(std::initializer_list<value_type> l);
    ~queue();

    inline reference front();
    inline const_reference front() const;
    inline reference back();
    inline const_reference back() const;

    inline void push(const_reference x);
    inline void push(value_type &&x);
    inline void pop();
    inline bool empty() const noexcept;
    inline size_type size() const noexcept;
private:
    std::list<value_type> list;
};

}

#include "s21_queue.inl"

#endif