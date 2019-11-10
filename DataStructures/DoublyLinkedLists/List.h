#ifndef __LIST__
#define __LIST__

template <typename Object>
class List
{
private:
  struct Node;
  Node *_head;
  Node *_tail;
  int _size;
  void init();

public:
  class const_iterator;
  class iterator;
  List();
  List(const List &);
  List &operator=(const List &);
  List(List &&);
  List &operator=(List &&);
  ~List();

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  int size() const;
  bool empty() const;

  Object &front();
  const Object &front() const;
  Object &back();
  const Object &back() const;

  void push_back(const Object &);
  void push_back(Object &&);
  void push_front(const Object &);
  void push_front(Object &&);
  void pop_back();
  void pop_front();
  void clear();
  iterator insert(iterator, const Object &);
  iterator insert(iterator, Object &&);
  iterator erase(iterator);
  iterator erase(iterator, iterator);
  void reverse_list();
};

template <typename Object>
struct List<Object>::Node
{
public:
  Object _data;
  Node *_next;
  Node *_previous;

  Node(const Object &data = Object{}, Node *next = nullptr, Node *previous = nullptr);
  Node(Object &&data, Node *next = nullptr, Node *previous = nullptr);
};

template <typename Object>
class List<Object>::const_iterator
{
protected:
  Node *_current;
  Object &retrieve() const;
  const_iterator(Node *current);

public:
  const_iterator();
  const Object &operator*();
  const_iterator &operator++();   // prefix
  const_iterator operator++(int); // postfix
  bool operator==(const const_iterator &rhs) const;
  bool operator!=(const const_iterator &rhs) const;

  friend class List<Object>;
};

template <typename Object>
class List<Object>::iterator : public const_iterator
{
protected:
  iterator(Node *current);

public:
  iterator();
  Object &operator*();
  const Object &operator*() const;
  iterator &operator++();
  iterator operator++(int);

  friend class List<Object>;
};

#include "List.tpp"

#endif