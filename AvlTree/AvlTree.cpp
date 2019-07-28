#include <list>
#include <algorithm>
#include "AvlTree.h"

///////////////////////////////////////////////////////////////////////////////

Node::Node(KeyType key)
    : key(key), height(1), left(nullptr), right(nullptr) { }

int Node::bfactor() const
{
    return heightOrZero(this->right) - heightOrZero(this->left);
}

void Node::fixHeight()
{
    auto left_height = heightOrZero(this->left);
    auto right_height = heightOrZero(this->right);
    this->height = std::max(left_height, right_height) + 1;
}

NodePtr Node::rotateRight(NodePtr& p)
{
    auto q = p->left;
    p->left = q->right;
    q->right = p;
    p->fixHeight();
    q->fixHeight();
    return q;
}

NodePtr Node::rotateLeft(NodePtr& q)
{
    auto p = q->right;
    q->right = p->left;
    p->left = q;
    q->fixHeight();
    p->fixHeight();
    return p;
}

NodePtr Node::balance(NodePtr& p)
{
    p->fixHeight();
    if (p->bfactor() == 2) {
        // Big Left rotate
        if (p->right->bfactor() < 0) {
            p->right = rotateRight(p->right);
        }
        return rotateLeft(p);
    }
    if (p->bfactor() == -2) {
        // Big Right rotate
        if (p->left->bfactor() > 0) {
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }
    return p;
}

uint8_t Node::heightOrZero(const NodePtr& node)
{
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

NodePtr Node::insert(NodePtr& root, KeyType key)
{
    if (root == nullptr) {
        root = std::make_shared<Node>(key);
        return root;
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return balance(root);
}

NodePtr Node::findMin(NodePtr root)
{
    if (root->left == nullptr) {
        return root;
    }
    return findMin(root->left);
}

NodePtr Node::find(NodePtr root, KeyType key)
{
    if (root == nullptr) {
        return nullptr;
    }
    if (key < root->key) {
        return find(root->left, key);
    }
    if (key > root->key) {
        return find(root->right, key);
    }
    return root;
}

NodePtr Node::removeMin(NodePtr& root)
{
    if (root->left == nullptr) {
        return root->right;
    }
    root->left = removeMin(root->left);
    return balance(root);
}

NodePtr Node::remove(NodePtr& root, KeyType key)
{
    if (root == nullptr) {
        return nullptr;
    }
    if (key < root->key) {
        root->left = remove(root->left, key);
    } else if (key > root->key) {
        root->right = remove(root->right, key);
    } else {
        // TODO: ?
        auto q = root->left;
        auto r = root->right;
        if (r == nullptr) {
            return q;
        }
        auto min_node = findMin(r);
        min_node->right = removeMin(r);
        min_node->left = q;
        return balance(min_node);
    }
    return balance(root);
}

void Tree::add(KeyType key)
{
    this->root = Node::insert(this->root, key);
}

void Tree::remove(KeyType key)
{
    this->root = Node::remove(this->root, key);
}

bool Tree::isContains(KeyType key) const
{
    return Node::find(this->root, key) != nullptr;
}

int Tree::getHeight() const
{
    return Node::heightOrZero(this->root);
}

///////////////////////////////////////////////////////////////////////////////
