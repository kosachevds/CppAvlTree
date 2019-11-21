#include "AvlTree.h"
#include "Tests.h"
#include <cstdlib>
#include <valarray>
#include <functional>
#include <vector>
#include <chrono>
#include <iostream>

void removeRandom(Tree& tree, int max_item);
int timeOperationUSec(Tree& tree, const std::function<void(Tree&)>& operation);
Tree createRandom(int item_count, int max_item);
std::valarray<int> timeRemoveUSec(int min_count, int max_count, int count_step);

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

void removeRandom(Tree& tree, int max_item)
{
    auto key = rand() % (max_item + 1);
    tree.remove(key);
}

int timeOperationUSec(Tree& tree, const std::function<void(Tree&)>& operation)
{
    auto begin = std::chrono::high_resolution_clock::now();
    operation(tree);
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - begin;
    return int(std::chrono::duration_cast<std::chrono::microseconds>(diff).count());
}

Tree createRandom(int item_count, int max_item)
{
    Tree tree;
    for (int i = 0; i < item_count; ++i) {
		tree.add(rand());
    }
    return tree;
}

std::valarray<int> timeRemoveUSec(int min_count, int max_count, int count_step)
{
    std::vector<int> times;
    for (int count = min_count; count <= max_count; count += count_step) {
        auto max_item = 10 * count;
        auto tree = createRandom(count, max_item);
        auto usec = timeOperationUSec(tree, [max_item] (Tree& tree)
        {
            removeRandom(tree, max_item);
        });
        times.push_back(usec);
    }
    return std::valarray<int>(times.data(), times.size());
}
