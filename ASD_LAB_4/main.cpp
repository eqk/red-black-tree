#include "my_set.h"
#include <set>

int main()
{
	RBTree<int> t1;
	std::set<int> s1;
	for (int i = 0; i < 1000; ++i) {
		t1.insert(i);
	}
	t1.insert(12);
}