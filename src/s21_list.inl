#ifndef S21_LIST_INL
#define S21_LIST_INL

namespace s21 {

template <class value_type>
list<value_type>::node::node(value_type value, node *next, node *prev) : value(value), next(next), prev(prev) {}

template <class value_type>
list<value_type>::iterator::iterator(const iterator &iter) {
    ptr = iter.ptr;
}

template <class value_type>
list<value_type>::iterator &list<value_type>::iterator::operator=(const iterator &iter) {
    return list<value_type>::iterator(iter);
}

template <class value_type>
bool list<value_type>::iterator::operator==(const iterator &iter) const {
    return ptr == iter.ptr;
}

template <class value_type>
bool list<value_type>::iterator::operator!=(const iterator &iter) const {
    return ptr != iter.ptr;
}

template <class value_type>
list<value_type>::iterator &list<value_type>::iterator::operator++() {
    ++ptr;
    return *this;
}

template <class value_type>
list<value_type>::iterator list<value_type>::iterator::operator++(int) {
    auto temp = list<value_type>::iterator(*this);
    ++ptr;
    return temp;
}

template <class value_type>
list<value_type>::iterator &list<value_type>::iterator::operator--() {
    --ptr;
    return *this;
}

template <class value_type>
list<value_type>::iterator list<value_type>::iterator::operator--(int) {
    auto temp = list<value_type>::iterator(*this);
    --ptr;
    return temp;
}

template <class value_type>
list<value_type>::iterator::reference list<value_type>::iterator::operator*() const {
    return *this;
}

template <class value_type>
list<value_type>::iterator::pointer list<value_type>::iterator::operator->() const {
    return this;
}

template <class value_type>
list<value_type>::const_iterator::const_iterator(const iterator &iter) {
    ptr = iter.ptr;
}

template <class value_type>
list<value_type>::iterator &list<value_type>::iterator::operator=(const iterator &iter) {
    return list<value_type>::iterator(iter);
}

template <class value_type>
bool list<value_type>::iterator::operator==(const iterator &iter) const {
    return ptr == iter.ptr;
}

template <class value_type>
bool list<value_type>::iterator::operator!=(const iterator &iter) const {
    return ptr != iter.ptr;
}

template <class value_type>
list<value_type>::iterator &list<value_type>::iterator::operator++() {
    ++ptr;
    return *this;
}

template <class value_type>
list<value_type>::iterator list<value_type>::iterator::operator++(int) {
    auto temp = list<value_type>::iterator(*this);
    ++ptr;
    return temp;
}

template <class value_type>
list<value_type>::iterator &list<value_type>::iterator::operator--() {
    --ptr;
    return *this;
}

template <class value_type>
list<value_type>::iterator list<value_type>::iterator::operator--(int) {
    auto temp = list<value_type>::iterator(*this);
    --ptr;
    return temp;
}

template <class value_type>
list<value_type>::iterator::reference list<value_type>::iterator::operator*() const {
    return *this;
}

template <class value_type>
list<value_type>::iterator::pointer list<value_type>::iterator::operator->() const {
    return this;
}

} // namespace s21

#endif