#include "min_heap_tree.h"
#include <math.h>
#include <stdio.h>

void print_plain_tree(struct HEAP_TREE tree)
{
    for(int i = 0; i <= tree.last_index; i++)
        printf("%d, ", tree.tree[i]);
    putchar('\n');
}


int _raise(const char* errmsg)
{
    printf("Error: %.*s\n", 80, errmsg); // with 80 as max length
    return 0;                            // dont exit on exception
}

void _swap(struct HEAP_TREE* tree, int i, int j)
{
    element_t temp = tree->tree[i];
    tree->tree[i]  = tree->tree[j];
    tree->tree[j]  = temp;
}

int _get_parent(int current_index)
{
    return (current_index - 1) / 2;
}

int _get_Lchild(int current_index)
{
    return current_index * 2 + 1;
}

int _get_Rchild(int current_index)
{
    return current_index * 2 + 2;
}

void _fix_topward(struct HEAP_TREE* tree, int current_index)
{
    element_t parent;
    while(current_index != 0)
    {
        parent = _get_parent(current_index);
        if(tree->tree[current_index] < tree->tree[parent])
        {
            _swap(tree, parent, current_index);
            current_index = parent;
        }
        else
            break;
    }
}


void _fix_backward(struct HEAP_TREE* tree, int current_index)
{
    element_t childL, childR, smallest_child;
    while(current_index <= tree->last_index)
    {
        childL = _get_Lchild(current_index);
        childR = _get_Rchild(current_index);
        if(childR > tree->last_index)
            childR = childL;
        if(childL > tree->last_index)
            break;
        smallest_child = (tree->tree[childR] < tree->tree[childL]) ? childR : childL;
        if(tree->tree[current_index] > tree->tree[smallest_child])
        {
            _swap(tree, current_index, smallest_child);
            current_index = smallest_child;
        }
        else
            break;
    }
}

struct HEAP_TREE create_heap_tree(int capacity)
{
    struct HEAP_TREE tree;
    tree.tree       = malloc(sizeof(element_t) * capacity);
    tree.capacity   = capacity;
    tree.last_index = -1;
    if(MHT_VERBOSE)
        puts("HEAP TREE CREATED");
    return tree;
}

void remove_heap_tree(struct HEAP_TREE* tree)
{
    free(tree->tree);
    tree->tree = NULL;
    if(MHT_VERBOSE)
        puts("HEAP TREE REMOVED");
}


void add_heap_tree(struct HEAP_TREE* tree, element_t element)
{
    if(tree->last_index + 1 < tree->capacity)
    {
        tree->tree[++tree->last_index] = element;
        _fix_topward(tree, tree->last_index);
        if(MHT_VERBOSE)
            puts("Adding new element");
    }
    else
    {
        if(_raise("Trying to add to a full tree"))
            exit(1);
    }
}


// get and remove the first element
element_t poll(struct HEAP_TREE* tree)
{
    if (tree->last_index < 0)
    {
        _raise("Trying to poll from an empty tree");
        return 0;
    }
    // TODO: comprobacion de si esta vacio
    element_t ret = tree->tree[0];
    _swap(tree, 0, tree->last_index--);

    _fix_backward(tree, 0);
    return ret;
}


void _putpadding(int s)
{
    for(int i = 0; i < s; i++)
        putchar(' ');
}


int _pow2(int n)
{
    if(n <= 0)
        return 1;
    else
        return 2 * _pow2(n - 1);
}

void print_tree_prettier(struct HEAP_TREE tree)
{
    int feetammount = (tree.capacity + 1) / 2;
    int levels      = (int)log2(tree.capacity)+1;
    int num_width   = 4;
    int total_width = (feetammount * 2 - 1) * num_width;
    int left_padding, mid_padding;
    int index = 0;
    for(int i = 0; i < total_width; i++)
        putchar('-');
    putchar('\n');
    for(int level = 0; level < levels; level++)
    {
        left_padding = (_pow2(levels - level - 1) - 1) * num_width;
        mid_padding = (2 * (_pow2(levels - level - 1) - 1) + 1) * num_width - 2;
        _putpadding(left_padding);
        for(int i = 0; i < _pow2(level); i++)
        {
            if(index > tree.last_index)
            {
                level = levels;
                break;
            }
            printf("(%.*d)", num_width, tree.tree[index++] % (int)pow(10, num_width));
            _putpadding(mid_padding);
        }
        putchar('\n');
    }
    for(int i = 0; i < total_width; i++)
        putchar('-');
    putchar('\n');
}

void print_tree(struct HEAP_TREE tree)
{
    int feetammount = (tree.capacity + 1) / 2;
    int levels      = (int)log2(tree.capacity + 1);
    int num_width   = 4;
    int total_width = (feetammount * 2 - 1) * num_width;
    int left_padding, mid_padding;
    int index = 0;
    for(int level = 0; level < levels; level++)
    {
        left_padding = (_pow2(levels - level - 1) - 1) * num_width;
        mid_padding  = (2 * (_pow2(levels - level - 1) - 1) + 1) * num_width;
        _putpadding(left_padding);
        for(int i = 0; i < _pow2(level); i++)
        {
            printf("%.*d", num_width, tree.tree[index++] % (int)pow(10, num_width));
            _putpadding(mid_padding);
        }
        putchar('\n');
    }
}
