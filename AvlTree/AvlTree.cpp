#include "AvlTree.h"

template<typename T>
void Tree<T>::add(T key)
{
	this->root = Node<T>::insert(this->root, key);
}

template<typename T>
void Tree<T>::remove(T key)
{
	this->root = Node<T>::remove(this->root, key);
}

template<typename T>
bool Tree<T>::isContains(T key) const
{
	return Node<T>::find(this->root, key) != nullptr;
}

template<typename T>
int Tree<T>::getHeight() const
{
	return Node<T>::heightOrZero(this->root);
}

template class Tree<int>;
