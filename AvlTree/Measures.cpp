#include "Measures.h"
#include "AvlTree.h"
#include "Utils.h"
#include <chrono>

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

std::vector<int> Measures::timesRemoving(int min_count, int max_count, int count_step)
{
	std::vector<int> times;
	auto items = Utils::createRandomSet(min_count);
	items.reserve(max_count);
    for (int count = min_count; count <= max_count; count += count_step) {
		items = Utils::addRandomItems(items, items.size() - count);
		auto tree = Tree::create(items.begin(), items.end());
		auto random_item = rand();

		auto begin = std::chrono::high_resolution_clock::now();
		tree.remove(random_item);
		auto end = std::chrono::high_resolution_clock::now();
		auto diff = end - begin;
        times.push_back(int(std::chrono::duration_cast<std::chrono::microseconds>(diff).count()));
    }
}
