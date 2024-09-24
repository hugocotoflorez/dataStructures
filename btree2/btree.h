#ifndef BTREE2_H
#define BTREE2_H

/* Use primitive
 * Allow pass any primitive data type
 * (int, char, long)
 * to values.
 */

#define USEPRM (void *) (long)

typedef struct __btree
{
    void **data;  // array of primitive type of size <= 8
                  // or pointer to allocated memory
                  // that user have to free
    int capacity; // max num of nodes
} BTree;

// create a tree of a given size
extern BTree  btree_create(int);
extern void   btree_grow(BTree *, int);
extern void   btree_delete(BTree *);
extern int    btree_get_root();
extern int    btree_get_parent(int);
extern int    btree_get_lchild(int);
extern int    btree_get_rchild(int);
extern void  *btree_set_value(BTree *, int, void *);
extern void  *btree_get_value(BTree , int);
extern BTree *btree_extend_lchild(BTree *, int, BTree);
extern BTree *btree_extend_rchild(BTree *, int, BTree *);
extern int    btree_get_height(BTree);
extern int    btree_get_relative_height(BTree, int);
extern void   btree_repr(BTree, const char *);

#define _putpadding(s)                \
    do                                \
    {                                 \
        for (int i = 0; i < (s); i++) \
            putchar(' ');             \
    } while (0);

#define _putseparator(s)              \
    do                                \
    {                                 \
        for (int i = 0; i < (s); i++) \
            putchar('-');             \
        putchar('\n');                \
    } while (0)

#define _pow2(n) (1 << (n))

#define btree_repr(tree, format_type, type)                                          \
    {                                                                                \
        int levels      = btree_get_height(tree);                                    \
        int num_width   = 4;                                                         \
        int total_width = _pow2(levels - 1) * (num_width) * 2 - 2;                   \
        int left_padding, mid_padding;                                               \
        int index = 0;                                                               \
        _putseparator(total_width);                                                  \
        for (int level = 0; level < levels; level++)                                 \
        {                                                                            \
            left_padding = (_pow2(levels - level - 1) - 1) * num_width;              \
            mid_padding = (2 * (_pow2(levels - level - 1) - 1) + 1) * num_width - 2; \
            _putpadding(left_padding);                                               \
            for (int i = 0; i < _pow2(level); i++)                                   \
            {                                                                        \
                if (index > tree.capacity)                                           \
                {                                                                    \
                    level = levels;                                                  \
                    break;                                                           \
                }                                                                    \
                printf("(%-*" format_type ")", num_width,                            \
                       (type) (long) tree.data[index++]);                            \
                _putpadding(mid_padding);                                            \
            }                                                                        \
            putchar('\n');                                                           \
        }                                                                            \
        _putseparator(total_width);                                                  \
    }


#endif // BTREE2_H
