#ifndef _MIN_HEAP_TREE
#define _MIN_HEAP_TREE

#include <stdlib.h>

#define MHT_VERBOSE   0
#define MHT_EXITONERR 0 // implementation definition, dont use

typedef int element_t;

struct HEAP_TREE
{
    element_t *tree;
    int        capacity;
    int        last_index;
    int (*comp)(void *, void *);
};

// example of how to declare a comparison function
int int_lessthan(void *a, void *b);

struct HEAP_TREE create_heap_tree(int height, int (*comp)(void *, void *));
void      add_heap_tree(struct HEAP_TREE *tree, element_t element);
void      remove_heap_tree(struct HEAP_TREE *tree);
element_t poll(struct HEAP_TREE *tree);


void print_plain_tree(struct HEAP_TREE tree); // print tree as array
void print_tree(struct HEAP_TREE tree);


#endif // !_MIN_HEAP_TREE
