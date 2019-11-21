#include "AvlTree.h"
#include "Tests.h"
#include <cstdlib>
#include <valarray>
#include <functional>
#include <vector>
#include <chrono>
#include <cassert>
#include <iostream>
#include <fstream>

template <typename InputIterator>
void write(std::ostream& stream, const InputIterator& begin, const InputIterator& end);
std::vector<int> measureHeightWithRandom(int items_count);
std::vector<int> measureHeightWithAcsending(int items_count);
void addRandom(Tree& tree, int max_item);
void removeRandom(Tree& tree, int max_item);
std::valarray<int> timeOperationUSec(int items_count, const std::function<void(Tree&)>& operation);
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

    //auto temp = measureHeightWithAcsending(100);

    //auto out_filename = "times.txt";
    //const auto launch_count = 10;
    //std::valarray<int> usec_array;

    //for (int i = 0; i < launch_count; ++i) {
    //    auto launch_times = timeRemoveUSec(100, 10000, 100);
    //    if (usec_array.size() == 0) {
    //        usec_array = launch_times;
    //    } else {
    //        usec_array += launch_times;
    //    }
    //}

    //std::ofstream out_file(out_filename);
    //write(out_file, begin(usec_array), end(usec_array));
    //out_file.close();

    return 0;
}

///////////////////////////////////////////////////////////////////////////////


template <typename InputIterator>
void write(std::ostream& stream, const InputIterator& begin, const InputIterator& end)
{
    for (auto it = begin; it != end; ++it) {
        stream << *it;
    }
}

std::vector<int> measureHeightWithRandom(int items_count)
{
    std::vector<int> heights(items_count);
    Tree tree;
    for (int i = 0; i < items_count; ++i) {
        heights[i] = tree.getHeight();
        addRandom(tree, items_count);
    }
    return heights;
}

std::vector<int> measureHeightWithAcsending(int items_count)
{
    std::vector<int> heights(items_count);
    Tree tree;
    for (int i = 0; i < items_count; ++i) {
        heights[i] = tree.getHeight();
        tree.add(i);
    }
    return heights;
}

void addRandom(Tree& tree, int max_item)
{
    tree.add(rand() % (max_item + 1));
    //tree.add(rand() % (2 * items_count + 1) - items_count);
}

void removeRandom(Tree& tree, int max_item)
{
    auto key = rand() % (max_item + 1);
    tree.remove(key);
}

std::valarray<int> timeOperationUSec(int items_count, const std::function<void(Tree&)>& operation)
{
    std::valarray<int> times(items_count);
    Tree tree;
    for (int i = 0; i < items_count; ++i) {
        times[i] = timeOperationUSec(tree, operation);
    }
    return times;
}

int timeOperationUSec(Tree& tree, const std::function<void(Tree&)>& operation)
{
    auto begin = std::chrono::high_resolution_clock::now();
    operation(tree);
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - begin;
    return std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
}

Tree createRandom(int item_count, int max_item)
{
    Tree tree;
    for (int i = 0; i < item_count; ++i) {
        addRandom(tree, max_item);
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
