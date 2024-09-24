#include "btree.h"
#include <stdlib.h>

inline int
btree_get_parent(int nindex)
{
    return (nindex - 1) >> 1;
}

inline int
btree_get_root()
{
    return 0;
}

inline int
btree_get_lchild(int nindex)
{
    return nindex * 2 + 1;
}

inline int
btree_get_rchild(int nindex)
{
    return nindex * 2 + 2;
}

BTree
btree_create(int height)
{
    BTree tree;
    int   capacity = (0x1 << height) - 1;
    tree.capacity  = capacity;
    tree.data      = malloc(sizeof(void *) * capacity);
    return tree;
}

void
btree_grow(BTree *tree, int height)
{
    int capacity = (0x1 << height) - 1;
    if (capacity > tree->capacity)
    {
        tree->capacity = capacity;
        tree->data     = realloc(tree->data, sizeof(void *) * capacity);
    }
}

void
btree_delete(BTree *tree)
{
    free(tree->data);
    *tree = (BTree){ 0, 0 };
}

inline void *
btree_get_value(BTree *tree, int nindex)
{
    return tree->data[nindex];
}

inline void *
btree_set_value(BTree *tree, int nindex, void *element)
{
    return (tree->data[nindex] = element);
}

int
_log2(unsigned int n)
{
    for (int i = 0; i < sizeof(n) * 4; i++)
    {
        if (n == 1)
            return i;
        n >>= 1;
    }
    return -1;
}

inline int
btree_get_height(BTree tree)
{
    return _log2(tree.capacity) + 1;
}

inline int
btree_get_relative_height(BTree tree, int nindex)
{
    return _log2(tree.capacity - nindex) + 1;
}

BTree *
btree_extend_lchild(BTree *tree, int pindex, BTree ext)
{
    return NULL;
}

BTree *
btree_extend_rchild(BTree *tree, int pindex, BTree *ext)
{
    return NULL;
}
