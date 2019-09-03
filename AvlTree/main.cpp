#include "AvlTree.h"
#include <ctime>
#include <cstdlib>
#include <valarray>
#include <functional>
#include <vector>
#include <chrono>
#include <cassert>
#include <iostream>
#include <fstream>
#include <unordered_set>

template <typename InputIterator>
void write(std::ostream& stream, const InputIterator& begin, const InputIterator& end);
std::vector<int> measureHeightWithRandom(int items_count);
std::vector<int> measureHeightWithAcsending(int items_count);
void addRandom(Tree& tree, int max_item);
void removeRandom(Tree& tree, int max_item);
std::valarray<int> timeOperationUSec(int items_count, const std::function<void(Tree&)>& operation);
int timeOperationUSec(Tree& tree, const std::function<void(Tree&)>& operation);
void testTreeAdd(int item_count);
void testTreeRemoveRandom(int item_count);
void testTreeRemoveRandomDeep(int item_count);
void testTreeRemoveSequence(int count);
Tree createRandom(int item_count, int max_item);
std::valarray<int> timeRemoveUSec(int min_count, int max_count, int count_step);

///////////////////////////////////////////////////////////////////////////////

int main()
{
    srand(unsigned(time(nullptr)));

    //testTreeAdd(100'000);
    //testTreeRemoveRandom(1000);
    //testTreeRemoveDeep(40'000);
    testTreeRemoveSequence(10);

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

void testTreeAdd(int item_count)
{
    Tree tree;
    std::vector<int> items(item_count);

    for (int i = 0; i < item_count; ++i) {
        auto item = rand();
        items[i] = item;
        tree.add(item);
    }

    for (auto item: items) {
        assert(tree.isContains(item));
    }

    std::cout << "Success!\n";

}

void testTreeRemoveRandom(int item_count)
{
    Tree tree;
    std::unordered_set<int> items;
    items.reserve(item_count);
    for (int i = 0; i < item_count; ++i) {
        int item;
        do {
            item = rand();
        } while (items.find(item) != items.end());
        items.insert(item);
        tree.add(item);
    }
    for (auto item : items) {
        tree.remove(item);
        assert(!tree.isContains(item));
    }

    std::cout << "Success!\n";
}

void testTreeRemoveRandomDeep(int item_count)
{
    Tree tree;
    std::unordered_set<int> items;
    items.reserve(item_count);
    for (int i = 0; i < item_count; ++i) {
        int item;
        do {
            item = rand();
        } while (items.find(item) != items.end());
        items.insert(item);
        tree.add(item);
    }
    for (auto it = items.begin(); it != items.end(); ++it) {
        tree.remove(*it);
        assert(!tree.isContains(*it));
        auto it2 = ++it;
        --it;
        for (;it2 != items.end(); ++it2) {
            assert(tree.isContains(*it2));
        }
    }

    std::cout << "Success!\n";

}

void testTreeRemoveSequence(int count)
{
    Tree tree;
    std::vector<int> items;
    items.reserve(count);
    for (int i = 0; i < count; ++i) {
        items.push_back(i);
        tree.add(i);
    }
    for (auto item : items) {
        tree.remove(item);
        assert(!tree.isContains(item));
    }
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
