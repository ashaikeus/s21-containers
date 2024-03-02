#ifndef S21_QUEUE_INL
#define S21_QUEUE_INL

namespace s21 {

template <class value_type>
queue<value_type>::queue() noexcept : list() {}

template <class value_type>
queue<value_type>::queue(const queue &q) {
     list = std::list(q.list); 
}

template <class value_type>
queue<value_type>::queue(queue &&q) {
    list = q.list;
    q.list.clear();
}

template <class value_type>
queue<value_type>::queue(std::initializer_list<value_type> l) : list() {
    for (auto i : l) {
        list.push_back(i);
    }
}

template <class value_type>
queue<value_type>::~queue() {
    list.clear();
}

template <class value_type>
inline typename queue<value_type>::reference queue<value_type>::front() {
    return list.front();
}

template <class value_type>
inline typename queue<value_type>::const_reference queue<value_type>::front() const {
    return list.front();
}

template <class value_type>
inline typename queue<value_type>::reference queue<value_type>::back() {
    return list.back();
}

template <class value_type>
inline typename queue<value_type>::const_reference queue<value_type>::back() const {
    return list.back();
}

template <class value_type>
inline void queue<value_type>::push(const_reference x) {
    list.push_back(x);
}

template <class value_type>
inline void queue<value_type>::push(value_type &&x) {
    list.push_back(x);
}

template <class value_type>
inline void queue<value_type>::pop() {
    list.erase(list.begin());
}

template <class value_type>
inline bool queue<value_type>::empty() const noexcept {
    return list.empty();
}

template <class value_type>
inline typename queue<value_type>::size_type queue<value_type>::size() const noexcept {
    return list.size();
}

}

#endif