#define POISON 0

#include "RBtree.h"

int main()
{
	RBtree tree = {};
	Construct(&tree);

	for (int i = 0; i < 100; ++i)
	{
	    Insert(&tree, i);
	}

	// printf("%d\n", LowerBound(&tree, 79)->key);
	// printf("%d\n", UpperBound(&tree, -2)->key);

	// for (int i = 0; i < 20; ++i)
	// {
	// 	Delete(&tree, i * 5);	
	// }

	// for (size_t i = 99; i > 0; --i)
	// {
	// 	printf("%d\n", KthStatistics(&tree, tree.root, i));
	// }

	// Delete(&tree, 40);
	// Delete(&tree, 15);

	TreeDump(&tree);
	Destruct(&tree);

	return 0;
}
