#include "RBtree.h"

void Construct(RBtree* tree)
{
	assert(tree);

	Node NIL = {};
	NIL.color = black;
	NIL.parent = &NIL;
	tree->NIL = &NIL;

	tree->root = tree->NIL;
	tree->cmp = IntCmp;
}

void Construct(RBtree* tree, int (*cmp)(const void*, const void*))
{
	assert(tree);

	Construct(tree);
	tree->cmp = cmp;
}

Node* FindParent(RBtree* tree, elem_t key)
{
	assert(tree);

	Node* tmp = tree->root;
	if (tmp == tree->NIL) return tree->NIL;

	Node* parent = tmp->parent;

	while (tmp != tree->NIL)
	{
		parent = tmp;
		if (tree->cmp(&key, &tmp->key) > 0)
		{
			tmp = parent->right;
		}
		else
		{
			tmp = parent->left;
		}
	}
	return parent;
}

Node* ConstructNode(RBtree* tree, Node* parent, elem_t key)
{
	Node* node = (Node*)calloc(1, sizeof(Node));
	node->parent = parent;
	node->left = tree->NIL;
	node->right = tree->NIL;
	node->color = red;
	node->key = key;

	return node;
}

void RotateRight(RBtree* tree, Node* node)
{	
	if (node == node->parent->left)
	{
		node->parent->left = node->left;		
	}
	else if (node == node->parent->right)
	{
		node->parent->right = node->left;
	}
	
	if (node->parent != tree->NIL)
	{
		node->left->parent = node->parent; // now we don't depend on the outside of "node"
	}
	else // if node == root
	{
		tree->root = node->left;
		node->left->parent = tree->NIL;
	}
	
	node->left = node->left->right;
	node->left->parent->right = node;
	node->parent = node->left->parent; 
	node->left->parent = node;
}

void RotateLeft(RBtree* tree, Node* node)
{	
	if (node == node->parent->right)
	{
		node->parent->right = node->right;		
	}
	else if (node == node->parent->left)
	{
		node->parent->left = node->right;
	}
	
	if (node->parent != tree->NIL)
	{
		node->right->parent = node->parent; // now we don't depend on the outside of "node"
	}
	else // if node == root
	{
		tree->root = node->right;
		node->right->parent = tree->NIL;
	}
	
	node->right = node->right->left;
	node->right->parent->left = node;
	node->parent = node->right->parent; 
	node->right->parent = node;
}

void InsertBalance(RBtree* tree, Node* node)
{
	assert(tree);

	while (node->parent->color != black)
	{
		if (node->parent == node->parent->parent->left)
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->color == red)
			{
				node->parent->color = black;
				uncle->parent->color = red;
				uncle->color = black;
				node = uncle->parent;
			}
			else //uncle->color == black
			{
				if (node == node->parent->right)
				{
					node = node->parent;
					RotateLeft(tree, node);
				}
				node->parent->color = black;
				node->parent->parent->color = red;
				RotateRight(tree, node->parent->parent);
				break;	
			}
		}

		else
		{
			Node* uncle = node->parent->parent->left;
			if (uncle->color == red)
			{
				node->parent->color = black;
				uncle->parent->color = red;
				uncle->color = black;
				node = uncle->parent;
			}
			else //uncle->color == black
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					RotateRight(tree, node);
				}
				node->parent->color = black;
				node->parent->parent->color = red;
				RotateLeft(tree, node->parent->parent);
				break;
			}

		}
	}
	tree->root->color = black;
}

void Insert(RBtree* tree, elem_t key)
{
	assert(tree);

	Node* parent = FindParent(tree, key);	
	Node* new_node = ConstructNode(tree, parent, key);

	if (parent == tree->NIL)
	{
		tree->root = new_node;
	}
	else
	{
		if (tree->cmp(&key, &parent->key) > 0)
		{
			parent->right = new_node;
		}
		else
		{
			parent->left = new_node;
		}
	}
	InsertBalance(tree, new_node);
}

void PrintNodes(RBtree* tree, Node* node, FILE* DumpFile)
{
	if (node->color == red)
	{
		// fprintf(DumpFile, "\"%p\"[style=\"filled\", fillcolor=\"#E16456\", fontcolor=\"black\", label=\"{%d|%p|{%p|%p|%p}}\"]", node, node->key, node,
		// 		node->left, node->parent, node->right);
		fprintf(DumpFile, "\"%p\"[style=\"filled\", fillcolor=\"#E16456\", fontcolor=\"black\", label=\"%d\"]", node, node->key);
	}
	else
	{ 
		// fprintf(DumpFile, "\"%p\"[style=\"filled\", fillcolor=\"#110F0F\", fontcolor=\"white\", label=\"{%d|%p|{%p|%p|%p}}\"]", node, node->key, node,
		// 		node->left, node->parent, node->right);
		fprintf(DumpFile, "\"%p\"[style=\"filled\", fillcolor=\"#110F0F\", fontcolor=\"white\", label=\"%d\"]", node, node->key);
	}
	if (node->left != tree->NIL)
	{
		fprintf(DumpFile, "\"%p\":sw->\"%p\";\n", node, node->left);
		PrintNodes(tree, node->left, DumpFile);
	}
	
	if (node->right != tree->NIL)
	{
		fprintf(DumpFile, "\"%p\":se->\"%p\";\n", node, node->right);
		PrintNodes(tree, node->right, DumpFile);
	}
}

Node* TreeMin(RBtree* tree, Node* node)
{
	Node* parent = node->parent;

	while (node != tree->NIL)
	{
		parent = node;
		node = node->left;
	}
	return parent;
}

Node* TreeMax(RBtree* tree, Node* node)
{
	Node* parent = node->parent;

	while (node != tree->NIL)
	{
		parent = node;
		node = node->right;
	}
	return parent;
}

Node* NodeNext(RBtree* tree, Node* node)
{
	if (node->right != tree->NIL)
	{
		return TreeMin(tree, node->right);
	}
	Node* parent = node->parent;
	while (parent != tree->NIL and node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	} 
	return parent;
}

Node* NodePrev(RBtree* tree, Node* node)
{
	if (node->left != tree->NIL)
	{
		return TreeMax(tree, node->left);
	}
	Node* parent = node->parent;
	while (parent != tree->NIL and node == parent->left)
	{
		node = parent;
		parent = parent->parent;
	} 
	return parent;	
}

Node* Find(RBtree* tree, elem_t key)
{
	Node* node = tree->root;

	while(node != tree->NIL)
	{
		if (tree->cmp(&node->key, &key) == 0)
		{
			return node;
		}
		else if (tree->cmp(&node->key, &key) > 0)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	return node;
}

bool IsFound(RBtree* tree, elem_t key)
{
	if (Find(tree, key) == tree->NIL)
	{
		return false;
	}
	return true;
}

void TreeDump(RBtree* tree)
{
	FILE* DumpFile = fopen("RBtree.txt", "w");

	fprintf(DumpFile, "digraph G{\n");
	fprintf(DumpFile, "node [shape=\"circle\", style=\"filled\", fillcolor=\"#C0FFC0\"];\n");

	PrintNodes(tree, tree->root, DumpFile);

	fprintf(DumpFile, "}");

	fclose(DumpFile);

	system("dot -Tjpg RBtree.txt > RBtree.jpg");
	system("start RBtree.jpg");
}

int IntCmp(const void* elem1, const void* elem2)
{
	return *(int*)elem1 - *(int*)elem2;
	//
}

void DestructNodes(RBtree* tree, Node* node)
{
	if (node != tree->NIL)
	{
		DestructNodes(tree, node->left);
		DestructNodes(tree, node->right);
		free(node);
	}
}	

void Destruct(RBtree* tree)
{
	assert(tree);

	DestructNodes(tree, tree->root);
	free(tree->NIL);
}