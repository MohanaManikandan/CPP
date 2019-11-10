#include "List.h"
#include <algorithm>

template <typename Object>
List<Object>::Node::Node(const Object &data, Node *next, Node *previous) : _next{next}, _previous{previous}, _data{data}
{
}

template <typename Object>
List<Object>::Node::Node(Object &&data, Node *next, Node *previous) : _next{next}, _previous{previous}, _data{std::move(data)}
{
}

template <typename Object>
void List<Object>::init()
{
    _size = 0;
    _head = new Node;
    _tail = new Node;
    _head->_next = _tail;
    _tail->_previous = _head;
}

template <typename Object>
List<Object>::List()
{
    init();
}

template <typename Object>
List<Object>::List(const List &rhs) : _size{rhs._size}
{
    init();
    for (auto x : rhs)
    {
        push_back(x);
    }
}

template <typename Object>
typename List<Object>::iterator List<Object>::begin()
{
    return _head->_next;
}

template <typename Object>
typename List<Object>::const_iterator List<Object>::begin() const
{
    return _head->_next;
}

template <typename Object>
typename List<Object>::iterator List<Object>::end()
{
    return _tail;
}

template <typename Object>
typename List<Object>::const_iterator List<Object>::end() const
{
    return _tail;
}

template <typename Object>
Object &List<Object>::front()
{
    return *begin();
}

template <typename Object>
const Object &List<Object>::front() const
{
    return *begin();
}

template <typename Object>
Object &List<Object>::back()
{
    return *(--end());
}

template <typename Object>
const Object &List<Object>::back() const
{
    return *(--end());
}

template <typename Object>
int List<Object>::size() const
{
    return _size;
}

template <typename Object>
bool List<Object>::empty() const
{
    return (size() == 0);
}

template <typename Object>
List<Object> &List<Object>::operator=(const List &rhs)
{
    List<Object> copy = rhs;
    std::swap(*this, copy);
    return *this;
}

template <typename Object>
List<Object>::List(List &&rhs) : _size{rhs._size}, _head{rhs._head}, _tail{rhs._tail}
{
    rhs._head = nullptr;
    rhs._tail = nullptr;
    rhs._size = 0;
}

template <typename Object>
List<Object> &List<Object>::operator=(List &&rhs)
{
    std::swap(_head, rhs._head);
    std::swap(_tail, rhs._tail);
    std::swap(_size, rhs._size);

    return *this;
}

template <typename Object>
List<Object>::~List()
{
    clear();
    delete _head;
    delete _tail;
}

template <typename Object>
List<Object>::const_iterator::const_iterator() : _current{nullptr}
{
}

template <typename Object>
List<Object>::const_iterator::const_iterator(Node *current) : _current{current}
{
}

template <typename Object>
Object &List<Object>::const_iterator::retrieve() const
{
    return _current->_data;
}

template <typename Object>
const Object &List<Object>::const_iterator::operator*()
{
    return retrieve();
}

template <typename Object>
typename List<Object>::const_iterator &List<Object>::const_iterator::operator++()
{
    _current = _current->_next;
    return *this;
}

template <typename Object>
typename List<Object>::const_iterator List<Object>::const_iterator::operator++(int)
{
    const_iterator old = *this;
    ++(*this);
    return old;
}

template <typename Object>
bool List<Object>::const_iterator::operator==(const const_iterator &rhs) const
{
    return _current == rhs._current;
}

template <typename Object>
bool List<Object>::const_iterator::operator!=(const const_iterator &rhs) const
{
    return !(*this == rhs);
}

template <typename Object>
List<Object>::iterator::iterator()
{
}

template <typename Object>
List<Object>::iterator::iterator(Node *current) : const_iterator(current)
{
}

template <typename Object>
Object &List<Object>::iterator::operator*()
{
    return const_iterator::retrieve();
}

template <typename Object>
const Object &List<Object>::iterator::operator*() const
{
    return const_iterator::retrieve();
}

template <typename Object>
typename List<Object>::iterator &List<Object>::iterator::operator++()
{
    this->_current = this->_current->_next;
    return *this;
}

template <typename Object>
typename List<Object>::iterator List<Object>::iterator::operator++(int)
{
    iterator old = *this;
    ++(*this);
    return old;
}

template <typename Object>
void List<Object>::push_back(const Object &object)
{
    insert(end(), object);
}

template <typename Object>
void List<Object>::push_back(Object &&object)
{
    insert(end(), std::move(object));
}

template <typename Object>
void List<Object>::push_front(const Object &object)
{
    insert(begin(), object);
}

template <typename Object>
void List<Object>::push_front(Object &&object)
{
    insert(begin(), std::move(object));
}

template <typename Object>
void List<Object>::pop_back()
{
    erase(--end());
}

template <typename Object>
void List<Object>::pop_front()
{
    erase(begin());
}

template <typename Object>
void List<Object>::clear()
{
    while (!empty())
    {
        pop_front();
    }
}

template <typename Object>
typename List<Object>::iterator List<Object>::insert(iterator ins_pos, const Object &object)
{
    Node *ins_node = ins_pos._current;
    ++_size;
    return (ins_node->_previous = ins_node->_previous->_next = new Node(object, ins_node, ins_node->_previous));
}

template <typename Object>
typename List<Object>::iterator List<Object>::insert(iterator ins_pos, Object &&object)
{
    Node *ins_node = ins_pos._current;
    ++_size;
    return (ins_node->_previous = ins_node->_previous->_next = new Node(std::move(object), ins_node, ins_node->_previous));
}

template <typename Object>
typename List<Object>::iterator List<Object>::erase(iterator erase_pos)
{
    Node *erase_node = erase_pos._current;
    iterator return_iter(erase_node->_next);
    erase_node->_previous->_next = erase_node->_next;
    erase_node->_next->_previous = erase_node->_previous;
    --_size;
    delete erase_node;
    return return_iter;
}

template <typename Object>
typename List<Object>::iterator List<Object>::erase(iterator start, iterator end)
{
    for (iterator it = start; it != end;)
    {
        it = erase(it);
    }
    return end;
}

template <typename Object>
void List<Object>::reverse_list()
{
    Node * current = _head;
    _tail = _head;
    Node * next = nullptr;
    Node * prev = nullptr;

    while(current)
    {
        next = current->_next;
        current->_next = prev;
        current->_previous = next;
        prev = current;
        current = next;
    }

    _head = prev;
}