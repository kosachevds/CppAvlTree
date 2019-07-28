#include <list>
#include "AvlTree.h"

struct Node
{
    KeyType key;
    uint8_t height;
    NodePtr left;
    NodePtr right;

    explicit Node(KeyType key);
    int bfactor() const;
    void fixHeight();
    NodePtr rotateRight();
    NodePtr rotateLeft();
    NodePtr balance();

    static uint8_t getHeight(NodePtr node);
    static NodePtr insert(NodePtr root, KeyType key);
    static NodePtr findMin(NodePtr root);
    static NodePtr find(NodePtr root, KeyType key);
    static NodePtr removeMin(NodePtr root);
    static NodePtr remove(NodePtr root, KeyType key);
};

std::list<Node> _nodes_buffer;

///////////////////////////////////////////////////////////////////////////////

Node::Node(KeyType key)
    : key(key), height(1), left(nullptr), right(nullptr) { }

int Node::bfactor() const
{
    return getHeight(this->right) - getHeight(this->left);
}

void Node::fixHeight()
{
    auto left_height = getHeight(this->left);
    auto right_height = getHeight(this->right);
    this->height = ((left_height > right_height) ? left_height : right_height) + 1;
    //this->height = std::max(left_height, right_height) + 1;
}

NodePtr Node::rotateRight()
{
    auto p = this;
    auto q = p->left;
    p->left = q->right;
    q->right = p;
    p->fixHeight();
    q->fixHeight();
    return q;
}

NodePtr Node::rotateLeft()
{
    auto q = this;
    auto p = q->right;
    q->right = p->left;
    p->left = q;
    q->fixHeight();
    p->fixHeight();
    return p;
}

NodePtr Node::balance()
{
    auto p = this;
    p->fixHeight();
    if (p->bfactor() == 2) {
        // Big Left rotate
        if (p->right->bfactor() < 0) {
            p->right = p->right->rotateRight();
        }
        return p->rotateLeft();
    }
    if (p->bfactor() == -2) {
        // Big Right rotate
        if (p->left->bfactor() > 0) {
            p->left = p->left->rotateLeft();
        }
        return p->rotateRight();
    }
    return p;
}

uint8_t Node::getHeight(NodePtr node)
{
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

NodePtr Node::insert(NodePtr root, KeyType key)
{
    if (root == nullptr) {
        _nodes_buffer.emplace_back(key);
        return &(_nodes_buffer.back()); // work good?
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return root->balance();
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

NodePtr Node::removeMin(NodePtr root)
{
    if (root->left == nullptr) {
        return root->right;
    }
    root->left = removeMin(root->left);
    return root->balance();
}

NodePtr Node::remove(NodePtr root, KeyType key)
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
        auto min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return min->balance();
    }
    return root->balance();
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
    return Node::getHeight(this->root);
}

///////////////////////////////////////////////////////////////////////////////
