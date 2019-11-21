#ifndef TESTS_H
#define TESTS_H

#include <unordered_set>

class Tests
{
public:
	Tests(int items_count);
	Tests adding() const;
	Tests removingRandom() const;
	Tests removingRandomDeep() const;
	Tests removingSequence() const;
	static std::unordered_set<int> createRandomSet(int count);
private:
	int _item_count;
};

#endif
