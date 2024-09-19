#ifndef BTREE_H
#define BTREE_H

/* Use primitive
 * Allow pass any primitive data type
 * (int, char, long)
 * to values.
 */
#define USEPRM (void *)

typedef struct __btree
{
    struct __btree *rchild; // subtree or NULL
    struct __btree *lchild;
    void           *value; // is primitive type of size <= 8
                           // or pointer to allocated memory
} BTree;

BTree *btree_empty();         // return a pointer to an initialized btree
void   btree_create(BTree *); // create a new btree
void  *btree_delete_tree(BTree *);        // delete tree and return NULL
void  *btree_get_value(BTree);            // get current value
void  *btree_set_value(BTree *, void *);  // set current value
BTree *btree_get_lchild(BTree);           // get left child
BTree *btree_get_rchild(BTree);           // get right child
BTree *btree_add_lchild(BTree *, void *); // create new lchild and set value
BTree *btree_add_rchild(BTree *, void *); // create new rchild and set value
BTree *btree_extend_lchild(BTree *, BTree *); // extend parent with subtree at left child
BTree *btree_extend_rchild(BTree *, BTree *); // extend parent with subtree at right child

#endif // BTREE_H
