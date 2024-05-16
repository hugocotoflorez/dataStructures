#ifndef _MIN_HEAP_TREE
#define _MIN_HEAP_TREE

#include <stdlib.h>

#define MHT_VERBOSE 1

typedef int element_t;

struct HEAP_TREE
{
    element_t* tree;
    int capacity;
    int last_index;
};

struct HEAP_TREE create_heap_tree(int capacity);
void add_heap_tree(struct HEAP_TREE* tree, element_t element);
void remove_heap_tree(struct HEAP_TREE* tree);
void print_tree(struct HEAP_TREE tree);
element_t poll(struct HEAP_TREE* tree);
void print_tree_prettier(struct HEAP_TREE tree);


#endif // !_MIN_HEAP_TREE
