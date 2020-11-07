#include "RBtree.h"


int main()
{
	RBtree tree = {};
	Construct(&tree);
	
	for (int i = 0; i < 50; ++i)
	{
		Insert(&tree, i);
	}
	// Insert(&tree, 20);
	// Insert(&tree, 10);
	// Insert(&tree, 30);
	// Insert(&tree, 35);
	// Insert(&tree, 36);
	// Insert(&tree, 37);
	// Insert(&tree, 25);
	// Insert(&tree, 15);
	// Insert(&tree, 15);
	// Insert(&tree, 5);
	
	// Insert(&tree, 3);
	// Insert(&tree, 6);
	// Insert(&tree, 14);
	// Insert(&tree, 32);
	// Insert(&tree, 40);
	// Insert(&tree, 22);
	// Insert(&tree, 27);
	// Insert(&tree, 16);

	printf("%d", IsFound(&tree, 48));
	TreeDump(&tree);
	
	Destruct(&tree);

	return 0;
}
