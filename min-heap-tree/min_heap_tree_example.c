#include "min_heap_tree.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int
r()
{
    return rand() % 10;
}

int
main(int argc, char **argv)
{
    struct HEAP_TREE tree;
    int              height;

    if (argc == 2)
        height = atoi(argv[1]);
    else
        height = 4;

    tree = create_heap_tree(height, int_lessthan);

    // the +1 is to force overflow
    for (int i = 0; i < tree.capacity + 1; i++)
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
