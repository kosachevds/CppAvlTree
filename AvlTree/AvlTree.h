#ifndef AVLTREE_H
#define AVLTREE_H

using KeyType = int;
struct Node;
using NodePtr = Node*;

// TODO: remade without raw pointers
//using NodePtr = std::shared_ptr<Node>;
//using NodePtr = std::unique_ptr<Node>;

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
