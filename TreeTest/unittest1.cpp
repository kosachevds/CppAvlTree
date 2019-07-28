#include "stdafx.h"

#include "AvlTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTest
{
	TEST_CLASS(TreeTest)
	{
	public:

		TEST_METHOD(TestAdd1000)
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
                Assert::IsTrue(tree.isContains(item), std::to_wstring(item).c_str());
            }

		}

	};
}