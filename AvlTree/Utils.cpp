#include "Utils.h"

std::unordered_set<int> Utils::createRandomSet(int count)
{
	std::unordered_set<int> items;
	items.reserve(count);
	while (int(items.size()) < count) {
		items.insert(rand());
	}
	return items;
}
