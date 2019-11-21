#ifndef UTILS_H
#include <unordered_set>

class Utils
{
public:
	Utils() = delete;
	static std::unordered_set<int> createRandomSet(int count);

};

#endif // !UTILS_H
