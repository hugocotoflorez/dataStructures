#include "min_heap_tree.h"
#include <stdio.h>

int int_lessthan(void*a, void*b)
{
    return *(int*) a < *(int*)b;
}
void _raise(const char* errmsg)
{
    printf("Error: %.*s\n", 80, errmsg); // with 80 as max length
    if (MHT_EXITONERR)
        exit(1);
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
        if(tree->comp((void*)&tree->tree[current_index], (void*)&tree->tree[parent]))
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
        smallest_child = tree->comp((void*)&tree->tree[childR], (void*)&tree->tree[childL]) ? childR : childL;
        if(tree->comp((void*)&tree->tree[smallest_child],(void*)&tree->tree[current_index] ))
        {
            _swap(tree, current_index, smallest_child);
            current_index = smallest_child;
        }
        else
            break;
    }
}

struct HEAP_TREE create_heap_tree(int capacity, int(*comp)(void*, void*))
{
    struct HEAP_TREE tree;
    tree.tree       = malloc(sizeof(element_t) * capacity);
    tree.capacity   = capacity;
    tree.last_index = -1;
    tree.comp = comp;
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
        _raise("Trying to add to a full tree");
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
void _putseparator(int s)
{
    for(int i = 0; i < s; i++)
        putchar('-');
    putchar('\n');
}

int _pow2(unsigned int n)
{
    return 1 << n;
}

int _log2(unsigned int n)
{
   for (int i = 0; i < sizeof (n) * 4; i++)
   {
       if (n == 1)
           return i;
       n >>= 1;
   }
   return -1;
}

void print_tree(struct HEAP_TREE tree)
{
    int levels      = (int)_log2(tree.capacity)+1;
    int num_width   = 4;
    int total_width = _pow2(levels-1)*(num_width)*2-2;
    int left_padding, mid_padding;
    int index = 0;
    _putseparator(total_width);
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
            printf("(%.*d)", num_width, tree.tree[index++]);
            _putpadding(mid_padding);
        }
        putchar('\n');
    }
    _putseparator(total_width);
}

void print_plain_tree(struct HEAP_TREE tree)
{
    for(int i = 0; i <= tree.last_index; i++)
        printf("%d, ", tree.tree[i]);
    putchar('\n');
}




#undef MHT_EXITONERR
#undef MHT_EXITONERR
