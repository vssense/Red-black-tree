#define POISON 0

#include "RBtree.h"

int main()
{
	RBtree tree = {};
	Construct(&tree);
	

	// Insert(&tree, 10);
	// Insert(&tree, 5);
	// Insert(&tree, 15);
	// Insert(&tree, 3);
	// Insert(&tree, 8);
	// Insert(&tree, 12);
	// Insert(&tree, 17);
	// Insert(&tree, 1);
	// Insert(&tree, 4);
	// Insert(&tree, 6);
	// Insert(&tree, 9);
	// Insert(&tree, 11);
	// Insert(&tree, 14);
	// Insert(&tree, 16);
	// Insert(&tree, 18);

	for (int i = 0; i < 50; ++i)
	{
	    Insert(&tree, i);
	}

	printf("%d\n", KthStatistics(&tree, tree.root, 24));
	printf("%d\n", LowerBound(&tree, 79)->key);
	printf("%d\n", UpperBound(&tree, -2)->key);

	// Insert(&tree, 10);
	// Insert(&tree, 12);
	// Insert(&tree, 13);
	// Insert(&tree, 14);
	// Insert(&tree, 1);
	// Insert(&tree, 3);
	// Insert(&tree, 6);
	// Insert(&tree, 7);
	// Insert(&tree, 9);
	// Insert(&tree, 17);
	// Insert(&tree, 19);
	// Insert(&tree, 18);
	// Insert(&tree, 30);
	// Insert(&tree, 31);
	// Insert(&tree, 32);
	// Insert(&tree, 28);
	// Insert(&tree, 29);
	// Insert(&tree, 4);
	// Insert(&tree, 5);
	// Insert(&tree, 2);
	// Insert(&tree, 8);
		
	// for (int i = 0; i < 10; ++i)
	// {
	// 	Delete(&tree, i * 5);	
	// }
	// Delete(&tree, tree.root->right->left);
	// Delete(&tree, tree.root->right->left);
	// Delete(&tree, tree.root->right->left);
	// Delete(&tree, tree.root->left->right);
	// Delete(&tree, tree.root->left->left);


	//Insert(&tree, 18);
	//Insert(&tree, 23);
	//Insert(&tree, 16);
	//Insert(&tree, 15);
	//Insert(&tree, 22);
	//Insert(&tree, 24);
	//Insert(&tree, 11);

	TreeDump(&tree);
	Destruct(&tree);

	return 0;
}