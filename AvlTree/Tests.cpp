#include "Tests.h"
#include "AvlTree.h"
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
	auto items = generateUniqueRandom();
	auto tree = Tree::create(items.begin(), items.end());
	for (auto item: items) {
		assert(tree.isContains(item));
	}
	return *this;
}

Tests Tests::removingRandom() const
{
	auto items = generateUniqueRandom();
	auto tree = Tree::create(items.begin(), items.end());
	for (auto item : items) {
		tree.remove(item);
		assert(!tree.isContains(item));
	}
	return *this;
}

Tests Tests::removingRandomDeep() const
{
	auto items = generateUniqueRandom();
	auto tree = Tree::create(items.begin(), items.end());
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
	Tree tree;
	for (int i = 0; i < this->_item_count; ++i) {
		tree.add(i);
	}
	for (int i = 0; i < this->_item_count; ++i) {
		tree.remove(i);
		assert(!tree.isContains(item));
	}
	return *this;
}

std::vector<int> Tests::generateUniqueRandom() const
{
	std::unordered_set<int> items;
	items.reserve(this->_item_count);
	while (int(items.size()) < this->_item_count) {
		items.insert(rand());
	}
	return std::vector<int>(items.begin(), items.end());
}
