#ifndef TESTS_H
#define TESTS_H

#include <vector>

class Tests
{
public:
	Tests(int items_count);
	Tests adding() const;
	Tests removingRandom() const;
	Tests removingRandomDeep() const;
	Tests removingSequence() const;
private:
	int _item_count;

	std::vector<int> generateUniqueRandom() const;
};

#endif
