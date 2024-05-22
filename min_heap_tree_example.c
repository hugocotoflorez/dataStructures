#include "min_heap_tree.h"
#include <stdlib.h>
#include <stdio.h>

unsigned int r()
{
    return rand()%10;
}

int main(int argc, char** argv)
{
    struct HEAP_TREE tree;
    int size;
    if (argc == 2)
        size = atoi(argv[1]);
    else size = 15;
    tree = create_heap_tree(size, int_lessthan);
    for(int i = 0; i < size+1; i++)
        add_heap_tree(&tree, r());
    print_tree(tree);
    printf("Min element: %d\n", poll(&tree));
    printf("Min element: %d\n", poll(&tree));
    printf("Min element: %d\n", poll(&tree));
    printf("Min element: %d\n", poll(&tree));
    printf("Min element: %d\n", poll(&tree));
    printf("Min element: %d\n", poll(&tree));
    printf("Min element: %d\n", poll(&tree));
    printf("Min element: %d\n", poll(&tree));
    printf("Min element: %d\n", poll(&tree));
    printf("Min element: %d\n", poll(&tree));
    print_tree(tree);
    remove_heap_tree(&tree);
    return 0;
}
