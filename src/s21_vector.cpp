#include "s21_vector.h"


template <typename value_type>
Vector<value_type>::Vector()
{
    m_size = 0u;
    m_capacity = 0u;
    m_data = nullptr;
}


template <typename value_type>
Vector<value_type>::Vector(size_type new_size)
{
    m_size = new_size;
    m_capacity = new_size;
    if (new_size) m_data = new value_type[new_size];
    else m_data = nullptr;
}

template <class value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const &items)
{
    m_size = items.size();
    m_capacity = items.size();
    m_data = new value_type[items.size()];

    int element = 0;
    for (auto item = items.begin(); item != items.end(); item++, element++)
    {
        m_data[element] = *item;
    }
}

// template <class T>
// void Vector<T>::reserve_more_capacity(size_type new_capacity)
// {
//     if (new_capacity > m_capacity)
//     {
//         value_type *buff = new value_type[new_capacity];
//         for (size_t i = 0; i < m_size; ++i)
//             buff[i] = std::move(m_data[i]);
//         delete[] m_data;
//         m_data = buff;
//         m_capacity = new_capacity;
//     }
// }

template <typename T>
size_t Vector<T>::size()
{
    return m_size;
}

template <typename T>
size_t Vector<T>::capacity()
{
    return m_capacity;
}

template <class value_type>
value_type *Vector<value_type>::get_data_pointer()
{
    return m_data;
}

// template <typename T>
// T Vector<T>::at(size_type i)
// {
//     return m_data[i];
// }


// template <typename T>
// void Vector<T>::push_back(T value)
// {
//     if (m_size == m_capacity)
//     {
//         reserve_more_capacity(m_size * 2);
//     }
//     m_data[m_size++] = value;
// }

// // externalizing template instances for correct linking, feel free to find more information
template class Vector<int>;
template class Vector<char>;
