#include "AvlTree.h"
#include "Tests.h"
#include "Measures.h"
#include <iostream>

int main()
{
#ifdef _DEBUG
	const auto TEST_ITEMS_COUNT = 1'000;
#else
	const auto TEST_ITEMS_COUNT = 10'000;
#endif
	Tests(TEST_ITEMS_COUNT)
		.adding()
		.removingRandom()
		.removingRandomDeep()
		.removingSequence();
	std::cout << "Tests passed!\n";

	auto heights = Measures(1000).heightsWithAscendingItems();

    return 0;
}
