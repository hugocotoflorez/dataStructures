#include "btree.h"
#include <stdlib.h>

BTree *
btree_empty()
{
    return calloc(1, sizeof(BTree));
}

void
btree_create(BTree *btree)
{
    btree = btree_empty();
}

void *
btree_get_value(BTree btree)
{
    return btree.value;
}

void *
btree_set_value(BTree *btree, void *value)
{
    btree->value = value;
    return btree;
}

BTree *
btree_get_lchild(BTree btree)
{
    return btree.lchild;
}

BTree *
btree_get_rchild(BTree btree)
{
    return btree.rchild;
}

BTree *
btree_add_lchild(BTree *parent, void *value)
{
    parent->lchild        = btree_empty();
    parent->lchild->value = value;
    return parent->lchild;
}

BTree *
btree_add_rchild(BTree *parent, void *value)
{
    parent->rchild        = btree_empty();
    parent->rchild->value = value;
    return parent->rchild;
}

BTree *
btree_extend_lchild(BTree *parent, BTree *lchild)
{
    parent->lchild = lchild;
    return lchild;
}

BTree *
btree_extend_rchild(BTree *parent, BTree *rchild)
{
    parent->rchild = rchild;
    return rchild;
}

void *
btree_delete_tree(BTree *parent)
{
    if (parent)
    {
        btree_delete_tree(parent->rchild);
        free(parent->rchild);
        btree_delete_tree(parent->lchild);
        free(parent->lchild);
    }
    return NULL;
}
