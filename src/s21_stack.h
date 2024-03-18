#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <utility>

namespace s21 {
template <class T>
class stack {
public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    stack() noexcept {}

    stack(const queue &other) {
        list = other.list;
    }

    stack(queue &&other) {
        list = std::move(other.list);
    }

    stack(std::initializer_list<value_type> init_list) {
        for (auto i : init_list) {
            list.push_back(i);
        }
    }

    ~stack() {
        list.clear();
    }

    inline reference front() {
        return list.front();
    }

    inline const_reference front() const {
        return list.front();
    }

    inline reference back() {
        return list.back();
    }

    inline const_reference back() const {
        return list.back();
    }

    inline void push(const_reference value) {
        list.push_back(value);
    }

    inline void push(value_type &&value) {
        list.push_back(value);
    }

    inline void pop() {
        list.pop_back();
    }

    inline reference top() {
        return *list.rbegin();
    }

    inline const_reference top() const {
        return *list.rbegin();
    }

    inline bool empty() const noexcept {
        return list.empty();
    }

    inline size_type size() const noexcept {
        return list.size();
    }
private:
    s21::list<value_type> list;
};

}

#endif // S21_STACK_H_