#include "AvlTree.h"
#include "Tests.h"
#include <iostream>

int main()
{
	const auto TEST_ITEMS_COUNT = 10'000;
	Tests(TEST_ITEMS_COUNT)
		.adding()
		.removingRandom()
		.removingRandomDeep()
		.removingSequence();
	std::cout << "Tests passed!\n";

    return 0;
}
