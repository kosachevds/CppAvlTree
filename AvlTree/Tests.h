#ifndef TESTS_H
#define TESTS_H

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
};

#endif
