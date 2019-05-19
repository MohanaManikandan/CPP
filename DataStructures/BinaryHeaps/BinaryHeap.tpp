#include "BinaryHeap.h"

template <typename Object>
BinaryHeap<Object>::BinaryHeap(int capacity) : _size{capacity}
{
    _array.reserve(_size);
}

template <typename Object>
BinaryHeap<Object>::BinaryHeap(const std::vector<Object> &items) : _size{items.size()}
{
    _array.reserve(items.size() * 2);
    int i = 0;
    for(auto x : items)
    {
        _array[++i] = x;
    }
    _size = i;
}

template <typename Object>
bool BinaryHeap<Object>::is_empty() const
{
    return _size == 0;
}

template <typename Object>
void BinaryHeap<Object>::insert(const Object &item)
{
    if (_size == _array.size() - 1)
    {
        _array.resize(_array.size() * 2);
    }

    int hole = ++_size;
    Object copy = item;
    _array[0] = std::move(copy);

    for (; item < _array[hole / 2]; hole /= 2)
    {
        _array[hole] = std::move(_array[hole / 2]);
    }

    _array[hole] = std::move(_array[0]);
}

template <typename Object>
void BinaryHeap<Object>::insert(Object &&item)
{
    if (_size == _array.size() - 1)
    {
        _array.resize(_array.size() * 2);
    }

    int hole = ++_size;
    Object copy = item;
    _array[0] = std::move(copy);

    for (; item < _array[hole / 2]; hole /= 2)
    {
        _array[hole] = std::move(_array[hole / 2]);
    }

    _array[hole] = std::move(_array[0]);
}

template <typename Object>
void BinaryHeap<Object>::delete_min()
{
    if (is_empty())
    {
        return;
    }

    _array[1] = std::move(_array[_size--]);
    percolate_down(1);
}

template <typename Object>
void BinaryHeap<Object>::delete_min(Object &item)
{
    if (is_empty())
    {
        return;
    }

    item = std::move(_array[1]);
    _array[1] = std::move(_array[_size--]);
    percolate_down(1);
}

template <typename Object>
void BinaryHeap<Object>::percolate_down(int hole)
{
    int child;
    Object copy = std::move(_array[hole]);

    for(; hole * 2 <= _size; hole = child)
    {
        child = 2 * hole;
        if(child != _size && _array[child + 1] < _array[child])
        {
            ++child;
        }
        
        if(_array[child] < copy)
        {
            _array[hole] = std::move(_array[child]);
        }
        else
        {
            break;
        }
    }

    _array[hole] = std::move(copy);
}

template <typename Object>
void BinaryHeap<Object>::make_empty()
{
    while(_size > 0)
    {
        delete_min();
    }
}

template <typename Object>
BinaryHeap<Object>::~BinaryHeap()
{
    make_empty();
}