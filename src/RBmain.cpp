#define POISON 0

#include "RBtree.h"

int main()
{
	RBtree tree = {};
	Construct(&tree);

	for (int i = 0; i < 20; ++i)
	{
	    Insert(&tree, i);
	}

	printf("%d\n", LowerBound(&tree, 5)->key);
	printf("%d\n", UpperBound(&tree, 5)->key);

	// TreeDump(&tree);
	Destruct(&tree);

	return 0;
}
