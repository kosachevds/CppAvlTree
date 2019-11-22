#include "Tests.h"
#include "AvlTree.h"
#include "Utils.h"
#include <cassert>
#include <unordered_set>
#include <ctime>

Tests::Tests(int items_count)
	: _item_count(items_count)
{
	srand(unsigned(time(nullptr)));
}

Tests Tests::adding() const
{
	auto items = Utils::createRandomSet(this->_item_count);
	auto tree = Tree<int>::create(items.begin(), items.end());
	for (auto item: items) {
		assert(tree.isContains(item));
	}
	return *this;
}

Tests Tests::removingRandom() const
{
	auto items = Utils::createRandomSet(this->_item_count);
	auto tree = Tree<int>::create(items.begin(), items.end());
	for (auto item : items) {
		tree.remove(item);
		assert(!tree.isContains(item));
	}
	return *this;
}

Tests Tests::removingRandomDeep() const
{
	auto items = Utils::createRandomSet(this->_item_count);
	auto tree = Tree<int>::create(items.begin(), items.end());
	for (auto it = items.begin(); it != items.end(); ++it) {
		tree.remove(*it);
		assert(!tree.isContains(*it));
		auto it2 = ++it;
		--it;
		for (; it2 != items.end(); ++it2) {
			assert(tree.isContains(*it2));
		}
	}
	return *this;
}

Tests Tests::removingSequence() const
{
	Tree<int> tree;
	for (int i = 0; i < this->_item_count; ++i) {
		tree.add(i);
	}
	for (int i = 0; i < this->_item_count; ++i) {
		tree.remove(i);
		assert(!tree.isContains(item));
	}
	return *this;
}

