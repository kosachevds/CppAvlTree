#include "AvlTree.h"
#include <ctime>
#include <cstdlib>
#include <valarray>
#include <fstream>
#include <functional>
#include <vector>
#include <chrono>
#include <cassert>
#include <iostream>

template <typename InputIterator>
void write(std::ostream& stream, const InputIterator& begin, const InputIterator& end);
std::vector<int> measureHeightWithRandom(int items_count);
void addRandom(Tree& tree, int max_item);
void removeRandom(Tree& tree, int max_item);
std::valarray<int> timeOperation(int items_count, const std::function<void(Tree&)>& operation);
void testTreeAdd1000();

///////////////////////////////////////////////////////////////////////////////

int main()
{
    srand(unsigned(time(nullptr)));
    testTreeAdd1000();
    //auto out_filename = "values.txt";

    //const auto items_count = 100'000;
    //const auto launch_count = 100;

    //std::valarray<int> results(items_count);
    //for (int i = 0; i < launch_count; ++i) {
    //    //auto results = measureHeightWithRandom(items_count);
    //    results += timeOperation(items_count, [items_count](auto tree)
    //    {
    //        addRandom(tree, items_count);
    //    });
    //}

    //std::ofstream out_file(out_filename);
    //write(out_file, begin(results), end(results));
    //out_file.close();
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

std::valarray<int> timeOperation(int items_count, const std::function<void(Tree&)>& operation)
{
    std::valarray<int> times(items_count);
    Tree tree;
    for (int i = 0; i < items_count; ++i) {
        auto begin = std::chrono::high_resolution_clock::now();
        operation(tree);
        auto end = std::chrono::high_resolution_clock::now();
        times[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    }
    return times;
}

void testTreeAdd1000()
{
    auto const ITEM_COUNT = 1000;
    Tree tree;
    std::vector<int> items(ITEM_COUNT);

    for (int i = 0; i < ITEM_COUNT; ++i) {
        auto item = rand();
        items[i] = item;
        tree.add(item);
    }

    for (auto item: items) {
        assert(tree.isContains(item), std::to_wstring(item).c_str());
    }

    std::cout << "Success!\n";

}
