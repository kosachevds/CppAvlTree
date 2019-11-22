#include <algorithm>
#include "AvlTree.h"

void Tree::add(KeyType key)
{
    this->root = Node<KeyType>::insert(this->root, key);
}

void Tree::remove(KeyType key)
{
    this->root = Node<KeyType>::remove(this->root, key);
}

bool Tree::isContains(KeyType key) const
{
    return Node<KeyType>::find(this->root, key) != nullptr;
}

int Tree::getHeight() const
{
    return Node<KeyType>::heightOrZero(this->root);
}

///////////////////////////////////////////////////////////////////////////////
