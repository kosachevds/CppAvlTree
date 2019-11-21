#include "Utils.h"

std::unordered_set<int> Utils::createRandomSet(int count)
{
	std::unordered_set<int> items;
	return addRandomItems(items, count);
}

std::unordered_set<int> Utils::addRandomItems(std::unordered_set<int>& set, int count)
{
	set.reserve(set.size() + count);
	while (int(set.size()) < count) {
		set.insert(rand());
	}
	return set;
}
