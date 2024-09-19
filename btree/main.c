#include <stdio.h>
#include "btree.h"

int main(int argc, char *argv[])
{
    BTree tree;
    btree_create(&tree);
    btree_set_value(&tree, USEPRM 10);
    btree_add_lchild(&tree, USEPRM 'a');
    btree_add_rchild(&tree, USEPRM 4);
    return 0;
}
