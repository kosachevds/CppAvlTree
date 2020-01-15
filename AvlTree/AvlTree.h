#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"

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
