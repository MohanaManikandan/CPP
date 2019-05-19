#ifndef __BINARY_HEAP__
#define __BINARY_HEAP__

#include <vector>
#include <iostream>

template <typename Object>
class BinaryHeap
{
private:
    std::vector<Object> _array;
    int _size;
    void percolate_down(int hole);

public:
    explicit BinaryHeap(int capacity = 100);
    explicit BinaryHeap(const std::vector<Object> &items);
    ~BinaryHeap();

    bool is_empty() const;
    void insert(const Object&);
    void insert(Object&&);
    void delete_min(Object&);
    void delete_min();
    void make_empty();
};

#include "BinaryHeap.tpp"

#endif