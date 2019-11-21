#ifndef UTILS_H
#include <unordered_set>

class Utils
{
public:
	Utils() = delete;
	static std::unordered_set<int> createRandomSet(int count);
	static std::unordered_set<int> addRandomItems(std::unordered_set<int>& set, int count);
};

#endif // !UTILS_H
