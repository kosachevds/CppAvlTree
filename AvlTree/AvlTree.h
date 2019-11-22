#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include <memory>

template <typename T>
class Tree final
{
public:
	Tree() = default;
    void add(T key);
    void remove(T key);
    bool isContains(T key) const;
    int getHeight() const;

	template <typename InputIterator>
	static Tree<T> create(InputIterator begin, InputIterator end);
private:
    NodePtr<T> root { nullptr };
};

///////////////////////////////////////////////////////////////////////////////

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

template <typename T>
template <typename InputIterator>
inline Tree<T> Tree<T>::create(InputIterator begin, InputIterator end)
{
	Tree<T> tree;
	for (auto it = begin; it != end; ++it) {
		tree.add(*it);
	}
	return tree;
}

#endif // AVLTREE_H
