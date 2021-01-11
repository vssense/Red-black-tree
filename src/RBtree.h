#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int ElemT;
const int max_key = 2 * (int)1e9;
const int min_key = -max_key;

typedef bool Color;

const bool black = true; 
const bool red   = false;


struct Node
{
    Color color = red;

    #ifdef POISON
    ElemT key = POISON;
    #else
    ElemT key;
    #endif

    Node* left   = nullptr;
    Node* right  = nullptr;
    Node* parent = nullptr; 

    size_t num = 0;
};

struct RBtree
{
    Node* root = nullptr;
    Node* nil  = nullptr;

    int (*cmp)(const void*, const void*);
};

void  Construct    (RBtree* tree);
void  Construct    (RBtree* tree, int (*cmp)(const void*, const void*));
void  Insert       (RBtree* tree, ElemT key);
void  Delete       (RBtree* tree, ElemT key);
void  Destruct     (RBtree* tree);

void  TreeDump     (RBtree* tree);
Node* NodeNext     (RBtree* tree, Node* node);
Node* NodePrev     (RBtree* tree, Node* node);
Node* FindNode     (RBtree* tree, ElemT key);
bool  Find         (RBtree* tree, ElemT key);

ElemT KthStatistics(RBtree* tree, Node* node, size_t k);
Node* UpperBound   (RBtree* tree, ElemT key);
Node* LowerBound   (RBtree* tree, ElemT key);
Node* TreeMin      (RBtree* tree, Node* node);
Node* TreeMax      (RBtree* tree, Node* node);
int   IntCmp       (const void* elem1, const void* elem2);
