#ifndef __VECTOR__
#define __VECTOR__

template <typename Object>
class Vector
{
  private:
    static const int SPARE_CAPACITY=16;
    Object *objects;
    int _capacity;
    int _size;

  public:
    explicit Vector(int init_size = 0); // Normal Constructor
    Vector(const Vector &);             // Copy Constructor
    Vector &operator=(const Vector &);  // Assignment
    Vector(Vector &&);                  // Move
    Vector &operator=(Vector &&);       // Move Assignment
    ~Vector();                          // Destructor

    int size() const;
    int capacity() const;
    bool empty() const;

    void resize(int new_size);
    void reserve(int new_capacity);

    Object &operator[](int index);
    const Object &operator[](int index) const;

    void push_back(const Object &); // Push Back A Const Object
    void push_back(Object &&);      // Push Back Using Move
    void pop_back();                // Throw away  last element
    const Object &back() const;     // Peek Last element
    Object &back();                 // Returns reference to last element

    typedef Object* iterator;
    typedef const Object* const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

};

#include "Vector.tpp"

#endif