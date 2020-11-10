#define POISON 0

#include "RBtree.h"


int main()
{
	RBtree tree = {};
	Construct(&tree);
	
	for (int i = 0; i < 50; ++i)
	{
		Insert(&tree, i);
	}
	Delete(&tree, tree.root->left);
	TreeDump(&tree);

	Destruct(&tree);

	return 0;
}
