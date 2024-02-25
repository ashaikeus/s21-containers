#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <initializer_list>
#include <utility>

template <class T>
class Vector
{
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;
        using size_type = size_t;
    private:
        size_type m_size;
        size_type m_capacity;
        value_type *m_data;
    public:
        Vector();
        explicit Vector(size_type new_size);
        Vector(std::initializer_list<value_type> const &items);

        // Vector(const Vector &v) : m_size(v.m_size), m_capacity(v.m_capacity), m_data(v.m_data) {};
        
        // Vector(Vector &&v) : m_size(v.m_size), m_capacity(v.m_capacity), m_data(v.m_data)
        // {
        //     v.m_data = nullptr;
        //     v.m_size = 0;
        // }

        ~Vector() { delete[] m_data; }


        size_type size();
        size_type capacity();
        value_type *get_data_pointer();

        value_type at(size_type i);

        void push_back(value_type value);
    private:
        void reserve_more_capacity(size_type new_capacity);
};

#endif
