#ifndef S21_LIST_H
#define S21_LIST_H


template <class T>
class List
{
    // private:
    //     size_t m_size;
    //     size_t m_capacity;
    //     T *arr;
    private:

    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;
        using size_type = size_t;
    public:
        List();
        List(size_type n);
        List(std::initializer_list<value_type> const &items);
        List(const List &l);
        List(List &&l);
        ~List();
        void operator=(List &ll);

        const_reference front();
        const_reference back();

        iterator begin();
        iterator end();

        bool empty();
        size_type size();
        size_type max_size();

        void clear();
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void push_back(const_reference value);
        void pop_back();
        void push_front(const_reference value);
        void pop_front();
        void swap(List& other);
        void merge(List& other);
        void splice(const_iterator pos, List& other);
        void reverse();
        void unique();
        void sort();

};


#endif 