#ifndef AVLTREE_H
#define AVLTREE_H
#include <memory>

using KeyType = int;
struct Node;
using NodePtr = std::shared_ptr<Node>;

struct Node
{
    KeyType key;
    uint8_t height;
    NodePtr left;
    NodePtr right;

    explicit Node(KeyType key);
    int bfactor() const;
    void fixHeight();

    static NodePtr rotateRight(NodePtr& p);
    static NodePtr rotateLeft(NodePtr& q);
    static NodePtr balance(NodePtr& p);
    static uint8_t heightOrZero(const NodePtr& node);
    static NodePtr insert(NodePtr& root, KeyType key);
    static NodePtr findMin(NodePtr root);
    static NodePtr find(NodePtr root, KeyType key);
    static NodePtr removeMin(NodePtr& root);
    static NodePtr remove(NodePtr& root, KeyType key);
};

class Tree final
{
public:
    Tree() = default;
    void add(KeyType key);
    void remove(KeyType key);
    bool isContains(KeyType key) const;
    int getHeight() const;
private:
    NodePtr root { nullptr };
};

#endif // AVLTREE_H
