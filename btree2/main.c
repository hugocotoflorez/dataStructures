#include "btree.h"
#include <stdio.h>

BTree  btree_create(int);
void   btree_grow(BTree *, int);
void   btree_delete(BTree *);
int    btree_get_parent(int);
int    btree_get_lchild(int);
int    btree_get_rchild(int);
void  *btree_set_value(BTree *, int, void *);
void  *btree_get_value(BTree , int);
BTree *btree_extend_lchild(BTree *, int, BTree);
BTree *btree_extend_rchild(BTree *, int, BTree *);
int    btree_get_height(BTree);
int    btree_get_relative_height(BTree, int);

int
main(int argc, char *argv[])
{
    int   height = 2;
    BTree tree   = btree_create(height); // create tree
    int   root   = btree_get_root();     // get root index
    int   lchild, rchild;

    btree_set_value(&tree, root, USEPRM 'A'); // set root value

    lchild = btree_get_lchild(root);            // get left child
    btree_set_value(&tree, lchild, USEPRM 'B'); // set left child value

    rchild = btree_get_rchild(root);            // get right child
    btree_set_value(&tree, rchild, USEPRM 'C'); // set right child value
    btree_repr(tree, "c", char);


    btree_delete(&tree);
    return 0;
}
