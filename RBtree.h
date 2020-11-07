#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define POISON 0

typedef int elem_t;
typedef bool Color;

const bool black = true; 
const bool red = false;

struct Node
{
	Color color = red;

	#ifdef POISON
	elem_t key = POISON;
	#else
	elem_t key;
	#endif

	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;	
};

struct RBtree
{
	Node* root = nullptr;
	Node* NIL = nullptr;

	int (*cmp)(const void*, const void*);
};

void Construct(RBtree* tree);
void Construct(RBtree* tree, int (*cmp)(const void*, const void*));

void Insert(RBtree* tree, elem_t key);

void TreeDump(RBtree* tree);

Node* NodeNext(RBtree* tree, Node* node);
Node* NodePrev(RBtree* tree, Node* node);

Node* Find(RBtree* tree, elem_t key);
bool IsFound(RBtree* tree, elem_t key);

void Destruct(RBtree* tree);

int IntCmp(const void* elem1, const void* elem2);