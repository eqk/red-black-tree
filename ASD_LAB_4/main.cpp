#include "my_set.h"
#include <set>
#include <iostream>
int main()
{
	RBTree<int> t1;
	std::set<int> s1;
	for (int i = 2; i < 1000; ++i) {
		t1.insert(i);
	}
	t1.insert(12);
	std::cout << *t1.end() << std::endl;
}