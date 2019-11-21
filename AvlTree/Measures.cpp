#include "Measures.h"
#include "AvlTree.h"

Measures::Measures(int item_count)
	: _item_count(item_count)
{
}

std::vector<int> Measures::heightsWithRandomItems() const
{
	std::vector<int> heights(this->_item_count);
	Tree tree;
	for (int i = 0; i < this->_item_count; ++i) {
		tree.add(rand());
		heights[i] = tree.getHeight();
	}
	return heights;
}

std::vector<int> Measures::heightsWithAscendingItems() const
{
	std::vector<int> heights(this->_item_count);
	Tree tree;
	for (int i = 0; i < this->_item_count; ++i) {
		tree.add(i);
		heights[i] = tree.getHeight();
	}
	return heights;
}
