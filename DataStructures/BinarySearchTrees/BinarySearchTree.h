#ifndef __BINARY_SEARCH_TREE__
#define __BINARY_SEARCH_TREE__

#include <ostream>

template <typename Object>
class BinarySearchTree
{
private:
    struct BinaryNode;
    BinaryNode *_root;

    bool contains(const Object &, BinaryNode *node);
    BinaryNode* find_min(BinaryNode *node) const;
    BinaryNode* find_max(BinaryNode *node) const;
    void insert(const Object &, BinaryNode *&node);
    void insert(Object &&, BinaryNode *&node);
    void remove(const Object &, BinaryNode *&node);
    void make_empty(BinaryNode *&node);
    void print_tree(BinaryNode* node, std::ostream &out) const;
    BinaryNode* clone(BinaryNode* node) const;
    int height(BinaryNode* node) const;

public:
    // Constructors
    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &);
    BinarySearchTree(BinarySearchTree &&);
    BinarySearchTree &operator=(const BinarySearchTree &);
    BinarySearchTree &operator=(BinarySearchTree &&);

    //Operations
    bool contains(const Object &);
    const Object &find_min() const;
    const Object &find_max() const;
    bool is_empty() const;
    void insert(const Object &);
    void insert(Object &&);
    void remove(const Object &);
    void make_empty();
    void print_tree(std::ostream &out = std::cout) const;
    int height() const;
};

template <typename Object>
struct BinarySearchTree<Object>::BinaryNode
{
public:
    Object _element;
    BinaryNode *_left;
    BinaryNode *_right;

    BinaryNode(const Object &element, BinaryNode *left, BinaryNode *right);
    BinaryNode(Object &&element, BinaryNode *left, BinaryNode *right);
};

#include "BinarySearchTree.tpp"

#endif