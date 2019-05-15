#include <ostream>
#include "BinarySearchTree.h"

template <typename Object>
BinarySearchTree<Object>::BinaryNode::BinaryNode(const Object &element, BinaryNode *left, BinaryNode *right)
    : _element{element}, _left{left}, _right{right}
{
}

template <typename Object>
BinarySearchTree<Object>::BinaryNode::BinaryNode(Object &&element, BinaryNode *left, BinaryNode *right)
    : _element{std::move(element)}, _left{left}, _right{right}
{
}

template <typename Object>
BinarySearchTree<Object>::BinarySearchTree() : _root{nullptr}
{
}

template <typename Object>
BinarySearchTree<Object>::~BinarySearchTree()
{
    make_empty(_root);
    _root = nullptr;
}

template <typename Object>
BinarySearchTree<Object>::BinarySearchTree(const BinarySearchTree &rhs) : _root{nullptr}
{
    _root = clone(rhs._root);
}

template <typename Object>
BinarySearchTree<Object>::BinarySearchTree(BinarySearchTree &&rhs) : _root{rhs._root}
{
    rhs._root = nullptr;
}

template <typename Object>
BinarySearchTree<Object> &BinarySearchTree<Object>::operator=(const BinarySearchTree &rhs)
{
    BinarySearchTree copy = rhs;
    std::swap(*this, copy);
    return *this;
}

template <typename Object>
BinarySearchTree<Object> &BinarySearchTree<Object>::operator=(BinarySearchTree &&rhs)
{
    std::swap(_root, rhs._root);
}

template <typename Object>
typename BinarySearchTree<Object>::BinaryNode *BinarySearchTree<Object>::clone(BinaryNode *node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else
    {
        return new BinaryNode(node->_element, clone(node->_left), clone(node->_right));
    }
}

template <typename Object>
bool BinarySearchTree<Object>::contains(const Object &element)
{
    return contains(element, _root);
}

template <typename Object>
bool BinarySearchTree<Object>::contains(const Object &element, BinaryNode *node)
{
    if (node == nullptr)
    {
        return false;
    }
    else if (node->_element > element)
    {
        return contains(element, node->_left);
    }
    else if (node->_element < element)
    {
        return contains(element, node->_right);
    }
    else
    {
        return true;
    }
}

template <typename Object>
const Object &BinarySearchTree<Object>::find_min() const
{
    BinaryNode *min_node = find_min(_root);
    return min_node ? min_node->_element : Object();
}

template <typename Object>
typename BinarySearchTree<Object>::BinaryNode *BinarySearchTree<Object>::find_min(BinaryNode *node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->_left == nullptr)
    {
        return node;
    }
    else
    {
        return find_min(node->_left);
    }
}

template <typename Object>
const Object &BinarySearchTree<Object>::find_max() const
{
    BinaryNode *max_node = find_max(_root);
    return max_node ? max_node->_element : Object();
}

template <typename Object>
typename BinarySearchTree<Object>::BinaryNode *BinarySearchTree<Object>::find_max(BinaryNode *node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->_right == nullptr)
    {
        return node;
    }
    else
    {
        return find_max(node->_right);
    }
}

template <typename Object>
bool BinarySearchTree<Object>::is_empty() const
{
    return _root == nullptr;
}

template <typename Object>
void BinarySearchTree<Object>::insert(const Object &element)
{
    insert(element, _root);
}

template <typename Object>
void BinarySearchTree<Object>::insert(const Object &element, BinaryNode *&node)
{
    if (node == nullptr)
    {
        node = new BinaryNode(element, nullptr, nullptr);
    }
    else if (element < node->_element)
    {
        insert(element, node->_left);
    }
    else if (element > node->_element)
    {
        insert(element, node->_right);
    }
    else
    {
        return;
    }
}

template <typename Object>
void BinarySearchTree<Object>::insert(Object &&element)
{
    insert(std::move(element), _root);
}

template <typename Object>
void BinarySearchTree<Object>::insert(Object &&element, BinaryNode *&node)
{
    if (node == nullptr)
    {
        node = new BinaryNode(std::move(element), nullptr, nullptr);
    }
    else if (element < node->_element)
    {
        insert(std::move(element), node->_left);
    }
    else if (element > node->_element)
    {
        insert(std::move(element), node->_right);
    }
    else
    {
        return;
    }
}

template <typename Object>
void BinarySearchTree<Object>::remove(const Object &element)
{
    remove(element, _root);
}

template <typename Object>
void BinarySearchTree<Object>::remove(const Object &element, BinaryNode *&node)
{
    if (node == nullptr)
    {
        return;
    }

    if (element < node->_element)
    {
        remove(element, node->_left);
    }
    else if (element > node->_element)
    {
        remove(element, node->_right);
    }
    else if (node->_left != nullptr and node->_right != nullptr)
    {
        node->_element = find_min(node->_right)->_element;
        remove(node->_element, node->_right);
    }
    else
    {
        BinaryNode *old = node;
        node = (node->_left != nullptr) ? node->_left : node->_right;
        delete old;
    }
}

template <typename Object>
void BinarySearchTree<Object>::make_empty()
{
    make_empty(_root);
}

template <typename Object>
void BinarySearchTree<Object>::make_empty(BinaryNode*& node)
{
    if(node != nullptr)
    {
        make_empty(node->_left);
        make_empty(node->_right);
        delete node;
    }
    node = nullptr;
}

template <typename Object>
void BinarySearchTree<Object>::print_tree(std::ostream& out) const
{
    print_tree(_root, out);
}

template <typename Object>
void BinarySearchTree<Object>::print_tree(BinaryNode* node, std::ostream& out) const
{
    if(node != nullptr)
    {
        print_tree(node->_left, out);
        out << node->_element << std::endl;
        print_tree(node->_right, out);
    }
}

template <typename Object>
int BinarySearchTree<Object>::height() const
{
    return height(_root);
}

template <typename Object>
int BinarySearchTree<Object>::height(BinaryNode* node) const
{
    if(nullptr == node)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(height(node->_left), height(node->_right));
    }
}