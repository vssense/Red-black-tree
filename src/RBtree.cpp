#include "RBtree.h"

Node* FindParent    (RBtree* tree, ElemT key);
Node* ConstructNode (RBtree* tree, Node* parent, ElemT key);
void  RotateRight   (RBtree* tree, Node* node);
void  RotateLeft    (RBtree* tree, Node* node);
void  InsertBalance (RBtree* tree, Node* node);
void  Transplant    (RBtree* tree, Node* old_node, Node* new_node);
void  FixNums       (RBtree* tree, Node* node);
void  DeleteBalance (RBtree* tree, Node* node);
void  DeleteNode    (RBtree* tree, Node* node);
void  PrintNodes    (RBtree* tree, Node* node, FILE* dump_file);
void  PrintNodesHard(RBtree* tree, Node* node, FILE* dump_file);
void  DestructNodes (RBtree* tree, Node* node);

void Construct(RBtree* tree)
{
    assert(tree);

    Node* nil = (Node*)calloc(1, sizeof(Node));
    assert(nil);

    nil->color  = black;
    nil->parent = nil;
    nil->left   = nil;
    nil->right  = nil;
    nil->num    = 0;
    tree->nil   = nil;

    tree->root = tree->nil;
    tree->cmp  = IntCmp;
}

void Construct(RBtree* tree, int (*cmp)(const void*, const void*))
{
    assert(tree);

    Construct(tree);
    tree->cmp = cmp;
}

Node* FindParent(RBtree* tree, ElemT key)
{
    assert(tree);

    Node* tmp = tree->root;
    if (tmp == tree->nil)
    {
        return tree->nil;
    }

    Node* parent = tmp->parent;

    while (tmp != tree->nil)
    {
        parent = tmp;
        parent->num++;

        if (tree->cmp(&key, &tmp->key) == 0)
        {
            FixNums(tree, tmp);
            return nullptr;
        }

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
void Insert(RBtree* tree, ElemT key)
{
    assert(tree);

    Node* parent   = FindParent(tree, key);

    if (parent == nullptr)
    {
        return;
    }

    Node* new_node = ConstructNode(tree, parent, key);

    if (parent == tree->nil)
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

void InsertBalance(RBtree* tree, Node* node)
{
    assert(tree);
    assert(node);

    while (node->parent->color != black)
    {
        if (node->parent == node->parent->parent->left)
        {
            Node* uncle = node->parent->parent->right;
            if (uncle->color == red)
            {
                node->parent->color  = black;
                uncle->parent->color = red;
                uncle->color         = black;
                node                 = uncle->parent;
            }
            else //uncle->color == black
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    RotateLeft(tree, node);
                }
                node->parent->color         = black;
                node->parent->parent->color = red;
                RotateRight(tree, node->parent->parent);
            }
        }
        else
        {
            Node* uncle = node->parent->parent->left;
            if (uncle->color == red)
            {
                node->parent->color  = black;
                uncle->parent->color = red;
                uncle->color         = black;
                node                 = uncle->parent;
            }
            else //uncle->color == black
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    RotateRight(tree, node);
                }
                node->parent->color         = black;
                node->parent->parent->color = red;
                RotateLeft(tree, node->parent->parent);
            }

        }
    }

    tree->root->color = black;
}

void Transplant(RBtree* tree, Node* old_node, Node* new_node)
{
    assert(tree);
    assert(old_node);
    assert(new_node);

    if (old_node->parent == tree->nil)
    {
        tree->root = new_node;
    }
    else if (old_node->parent->left == old_node)
    {
        old_node->parent->left = new_node;
    }
    else 
    {
        old_node->parent->right = new_node;
    }

    if (new_node != tree->nil)
    {
        new_node->num = old_node->num;
    }

    new_node->parent = old_node->parent;
}

Node* TreeMin(RBtree* tree, Node* node)
{
    assert(tree);
    assert(node);

    Node* parent = node->parent;

    while (node != tree->nil)
    {
        parent = node;
        node   = node->left;
    }

    return parent;
}

Node* TreeMax(RBtree* tree, Node* node)
{
    assert(tree);
    assert(node);

    Node* parent = node->parent;

    while (node != tree->nil)
    {
        parent = node;
        node   = node->right;
    }

    return parent;
}

void FixNums(RBtree* tree, Node* node)
{
    assert(tree);
    assert(node);

    while (node != tree->nil)
    {
        node->num--;
        node = node->parent;
    }
}

void Delete(RBtree* tree, ElemT key)
{
    assert(tree);

    Node* node_to_delete = FindNode(tree, key);

    if (node_to_delete != tree->nil)
    {
        DeleteNode(tree, node_to_delete);
    }
}

void DeleteNode(RBtree* tree, Node* node)
{
    assert(tree);
    assert(node);

    Node* node_for_balance = nullptr;
    Color original_color   = node->color;

    if (node->right == tree->nil)
    {
        node_for_balance = node->left;
        Transplant(tree, node, node->left);
    }
    else if (node->left == tree->nil)
    {
        node_for_balance = node->right;
        Transplant(tree, node, node->right);
    }
    else
    {
        Node* closest    = TreeMin(tree, node->right);
        original_color   = closest->color;
        node_for_balance = closest->right;

        if (closest->parent ==  node)
        {
            node_for_balance->parent = closest;
        }
        else
        {
            Transplant(tree, closest, closest->right);
            // closest->num--;
            closest->right         = node->right;
            closest->right->parent = closest;
        }

        Transplant(tree, node, closest);
        closest->left         = node->left;
        closest->left->parent = closest;
        closest->color        = node->color;
    }

    FixNums(tree, node_for_balance->parent);

    free(node);

    if (original_color == black)
    {
        DeleteBalance(tree, node_for_balance);
    }
}

void DeleteBalance(RBtree* tree, Node* node)
{
    assert(tree);
    assert(node);
    
    while (node != tree->root && node->color == black)
    {
        if (node == node->parent->left)
        {
            Node* brother = node->parent->right;
            if (brother->color == red) 
            {
                brother->color      = black;
                node->parent->color = red;
                RotateLeft(tree, node->parent);
                brother = node->parent->right;
            }

            if (brother->left->color == black &&
                brother->right->color == black)
            {
                brother->color = red;
                node           = node->parent;
            }
            else 
            {
                if (brother->right->color == black)
                {
                    brother->left->color = black;
                    brother->color       = red;
                    RotateRight(tree, brother);
                    brother = node->parent->right;
                }
                
                brother->color        = node->parent->color;
                node->parent->color   = black;
                brother->right->color = black;
                RotateLeft(tree, node->parent);
                node = tree->root;
            }
        }
        else /*(node == node->parent->right)*/
        {
            Node* brother = node->parent->left;
            if (brother->color == red) 
            {
                brother->color      = black;
                node->parent->color = red;
                RotateRight(tree, node->parent);
                brother = node->parent->left;
            }

            if (brother->left->color == black &&
                brother->right->color == black)
            {
                brother->color = red;
                node           = node->parent;
            }
            else 
            {
                if (brother->left->color == black)
                {
                    brother->right->color = black;
                    brother->color        = red;
                    RotateLeft(tree, brother);
                    brother = node->parent->left;
                }

                brother->color       = node->parent->color;
                node->parent->color  = black;
                brother->left->color = black;
                RotateRight(tree, node->parent);
                node = tree->root;
            }   
        }
    }

    node->color = black;
}


Node* ConstructNode(RBtree* tree, Node* parent, ElemT key)
{
    assert(tree);
    assert(parent);

    Node* node = (Node*)calloc(1, sizeof(Node));
    assert(node);

    node->parent = parent;
    node->left   = tree->nil;
    node->right  = tree->nil;
    node->color  = red;
    node->key    = key;
    node->num    = 1;

    return node;
}

void RotateRight(RBtree* tree, Node* node)
{
    assert(tree);
    assert(node);

    Node* left_child = node->left;
    node->left       = left_child->right;

    if (left_child->right != tree->nil)
    {
        left_child->right->parent = node;
    }

    left_child->parent = node->parent;

    if (node->parent == tree->nil)
    {
        tree->root = left_child;
    }
    else if (node->parent->right == node)
    {
        node->parent->right = left_child;
    }
    else
    {
        node->parent->left = left_child;
    }

    left_child->right = node;
    node->parent      = left_child;
    node->num         = node->left->num + node->right->num + 1;
    left_child->num   = left_child->left->num + left_child->right->num + 1;
}

void RotateLeft(RBtree* tree, Node* node)
{   
    assert(tree);
    assert(node);

    Node* right_child = node->right;
    node->right       = right_child->left;

    if (right_child->left != tree->nil)
    {
        right_child->left->parent = node;
    }

    right_child->parent = node->parent;

    if (node->parent == tree->nil)
    {
        tree->root = right_child;
    }
    else if (node->parent->left == node)
    {
        node->parent->left = right_child;
    }
    else
    {
        node->parent->right = right_child;
    }

    right_child->left = node;
    node->parent      = right_child;
    node->num         = node->left->num + node->right->num + 1;
    right_child->num  = right_child->left->num + right_child->right->num + 1;
}

Node* NodeNext(RBtree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->right != tree->nil)
    {
        return TreeMin(tree, node->right);
    }

    Node* parent = node->parent;
    while (parent != tree->nil && node == parent->right)
    {
        node   = parent;
        parent = parent->parent;
    }

    return parent;
}

Node* NodePrev(RBtree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->left != tree->nil)
    {
        return TreeMax(tree, node->left);
    }

    Node* parent = node->parent;
    while (parent != tree->nil && node == parent->left)
    {
        node   = parent;
        parent = parent->parent;
    }

    return parent;  
}

Node* FindNode(RBtree* tree, ElemT key)
{
    assert(tree);

    Node* node = tree->root;

    while(node != tree->nil)
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

bool Find(RBtree* tree, ElemT key)
{
    assert(tree);

    if (FindNode(tree, key) == tree->nil)
    {
        return false;
    }

    return true;
}

ElemT KthStatistics(RBtree* tree, Node* node, size_t k)//!!! multiset
{
    assert(tree);
    assert(node);

    if (k == node->left->num)
    {
        return node->key;
    }

    if (k < node->left->num)
    {
        return KthStatistics(tree, node->left, k);
    }

    return KthStatistics(tree, node->right, k - node->left->num - 1);
}

Node* UpperBound(RBtree* tree, ElemT key)
{
    Node* min      = tree->nil;
    tree->nil->key = max_key;

    Node* live_node = tree->root;

    while (live_node != tree->nil)
    {
        if (tree->cmp(&live_node->key, &key) == 0)
        {
            return NodeNext(tree, live_node);
        }
        else if (tree->cmp(&live_node->key, &key) > 0)
        {
            if (tree->cmp(&live_node->key, &min->key) < 0)
            {
                min = live_node;
            }

            live_node = live_node->left;
        }
        else
        {
            live_node = live_node->right;
        }
    }

    return min;
}

Node* LowerBound(RBtree* tree, ElemT key)
{
    Node* max      = tree->nil;
    tree->nil->key = min_key;

    Node* live_node = tree->root;

    while (live_node != tree->nil)
    {
        if (tree->cmp(&live_node->key, &key) == 0)
        {
            return NodePrev(tree, live_node);
        }
        else if (tree->cmp(&live_node->key, &key) > 0)
        {

            live_node = live_node->left;
        }
        else
        {
            if (tree->cmp(&live_node->key, &max->key) > 0)
            {
                max = live_node;
            }

            live_node = live_node->right;
        }
    }

    return max;
}

void TreeDump(RBtree* tree)
{
    assert(tree);

    FILE* dump_file = fopen("RBtree.txt", "w");

    fprintf(dump_file, "digraph G{\n");
    fprintf(dump_file, "node [shape=\"circle\", style=\"filled\", fillcolor=\"#C0FFC0\"]\n");

    PrintNodes(tree, tree->root, dump_file);

    fprintf(dump_file, "}");

    fclose(dump_file);

    system("dot -Tjpg RBtree.txt > RBtree.jpg");
    system("start RBtree.jpg");
}

void PrintNodes(RBtree* tree, Node* node, FILE* dump_file)
{
    assert(tree);
    assert(node);

    if (node->color == red)
    {
        fprintf(dump_file, "\"%p\"[style=\"filled\", fillcolor=\"#E16456\", fontcolor=\"black\", label=\"%d\"]", node, node->key);
    }
    else
    { 
        fprintf(dump_file, "\"%p\"[style=\"filled\", fillcolor=\"#110F0F\", fontcolor=\"white\", label=\"%d\"]", node, node->key);
    }
    if (node->left != tree->nil)
    {
        fprintf(dump_file, "\"%p\":sw->\"%p\";\n", node, node->left);
        PrintNodes(tree, node->left, dump_file);
    }
    
    if (node->right != tree->nil)
    {
        fprintf(dump_file, "\"%p\":se->\"%p\";\n", node, node->right);
        PrintNodes(tree, node->right, dump_file);
    }
}

void PrintNodesHard(RBtree* tree, Node* node, FILE* dump_file)
{
    assert(tree);
    assert(node);

    if (node->color == red)
    {
        fprintf(dump_file, "\"%p\" [shape=\"record\", style=\"filled\", fillcolor=\"#E16456\","
                "fontcolor=\"black\", label=\"{%d|%p|{%p|%p|%p}}\"]", node, node->key, node,
                node->left, node->parent, node->right);
    }
    else
    { 
        fprintf(dump_file, "\"%p\" [shape=\"record\", style=\"filled\", fillcolor=\"#110F0F\","
                "fontcolor=\"white\", label=\"{%d|%p|{%p|%p|%p}}\"]", node, node->key, node,
                node->left, node->parent, node->right);
    }
    if (node->left != tree->nil)
    {
        fprintf(dump_file, "\"%p\":sw->\"%p\";\n", node, node->left);
        PrintNodesHard(tree, node->left, dump_file);
    }
    
    if (node->right != tree->nil)
    {
        fprintf(dump_file, "\"%p\":se->\"%p\";\n", node, node->right);
        PrintNodesHard(tree, node->right, dump_file);
    }
}

int IntCmp(const void* elem1, const void* elem2)
{
    return *(int*)elem1 - *(int*)elem2;
}

void Destruct(RBtree* tree)
{
    assert(tree);

    DestructNodes(tree, tree->root);
    free(tree->nil);
}

void DestructNodes(RBtree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node != tree->nil)
    {
        DestructNodes(tree, node->left);
        DestructNodes(tree, node->right);
        free(node);
    }
}   