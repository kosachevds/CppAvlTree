#ifndef MEASURES_H

#include <vector>

class Measures
{
public:
	Measures(int item_count);
	std::vector<int> heightsWithRandomItems() const;
	std::vector<int> heightsWithAscendingItems() const;
	static std::vector<int> timesRemoving(int min_count, int max_count, int count_step);
private:
	int _item_count;
};

#endif // !MEASURES_H
