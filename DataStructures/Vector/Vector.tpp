#include "Vector.h"
#include <algorithm>

template <typename Object>
Vector<Object>::Vector(int init_size) : _size(init_size), _capacity(init_size + SPARE_CAPACITY)
{
    objects = new Object[_capacity];
}

template <typename Object>
Vector<Object>::Vector(const Vector &rhs) : _size(rhs._size), _capacity(rhs._capacity), objects{nullptr}
{
    objects = new Object[_capacity];
    for (int i = 0; i < rhs._size; ++i)
    {
        objects[i] = rhs.objects[i];
    }
}

template <typename Object>
Vector<Object> &Vector<Object>::operator=(const Vector &rhs)
{
    Vector copy = rhs;
    std::swap(*this, copy);
    return *this;
}

template <typename Object>
Vector<Object>::Vector(Vector &&rhs) : _size{rhs._size}, _capacity{rhs._capacity}, objects{rhs.objects}
{
    rhs._size = 0;
    rhs._capacity = 0;
    rhs.objects = nullptr;
}

template <typename Object>
Vector<Object> &Vector<Object>::operator=(Vector &&rhs)
{
    std::swap(_size, rhs._size);
    std::swap(_capacity, rhs._capacity);
    std::swap(objects, rhs.objects);
}

template <typename Object>
Vector<Object>::~Vector()
{
    delete[] objects;
}

template <typename Object>
int Vector<Object>::size() const
{
    return _size;
}

template <typename Object>
int Vector<Object>::capacity() const
{
    return _capacity;
}

template <typename Object>
bool Vector<Object>::empty() const
{
    return size() == 0;
}

template <typename Object>
void Vector<Object>::resize(int new_size)
{
    if (new_size > _capacity)
    {
        reserve(new_size * 2);
        return;
    }
    _size = new_size;
}

template <typename Object>
void Vector<Object>::reserve(int new_capacity)
{
    if (new_capacity < _size)
    {
        return;
    }

    Object *local = new Object[new_capacity];
    _capacity = new_capacity;
    for (int i = 0; i < _size; ++i)
    {
        local[i] = std::move(objects[i]);
    }
    delete[] objects;
    objects = local;
}

template <typename Object>
const Object &Vector<Object>::operator[](int index) const
{
    return objects[index];
}

template <typename Object>
Object &Vector<Object>::operator[](int index)
{
    return objects[index];
}

template <typename Object>
void Vector<Object>::push_back(const Object &item)
{
    if (_size == _capacity)
    {
        reserve(_capacity * 2 + 1);
    }
    objects[_size++] = std::move(item);
}

template <typename Object>
void Vector<Object>::push_back(Object &&item)
{
    if (_size == _capacity)
    {
        reserve(_capacity * 2 + 1);
    }
    objects[_size++] = std::move(item);
}

template <typename Object>
void Vector<Object>::pop_back()
{
    --_size;
}

template <typename Object>
const Object &Vector<Object>::back() const
{
    return objects[_size - 1];
}

template <typename Object>
Object &Vector<Object>::back()
{
    return objects[_size - 1];
}

template <typename Object>
typename Vector<Object>::iterator Vector<Object>::begin()
{
    return &objects[0];
}

template <typename Object>
typename Vector<Object>::const_iterator Vector<Object>::begin() const
{
    return &objects[0];
}

template <typename Object>
typename Vector<Object>::iterator Vector<Object>::end()
{
    return &objects[_size];
}

template <typename Object>
typename Vector<Object>::const_iterator Vector<Object>::end() const
{
    return &objects[_size];
}