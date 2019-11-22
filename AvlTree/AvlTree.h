#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include <memory>

class Tree final
{
public:
	using KeyType = int;
	Tree() = default;
    void add(KeyType key);
    void remove(KeyType key);
    bool isContains(KeyType key) const;
    int getHeight() const;

	template <typename InputIterator>
	static Tree create(InputIterator begin, InputIterator end);
private:
    NodePtr<KeyType> root { nullptr };
};

template<typename InputIterator>
inline Tree Tree::create(InputIterator begin, InputIterator end)
{
	Tree tree;
	for (auto it = begin; it != end; ++it) {
		tree.add(*it);
	}
	return tree;
}

#endif // AVLTREE_H
