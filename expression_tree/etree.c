#include "btree.h"
#include "stack.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * El stack de numeros tiene que ser un stack de arboles
 * donde los nueros son arboles de in solo elemento y al
 * hacer un merge se extienden las ramas.
 */

// clang-format off
static int PRIORITY[] = {
    ['+'] = 0,
    ['-'] = 0,
    ['*'] = 1,
    ['/'] = 1,
    ['^'] = 2,
    ['('] = 3,
};
// clang-format on

void
print_inorden(BTree tree, int index)
{
    if (index < tree.capacity)
    {
        print_inorden(tree, btree_get_lchild(index));
        printf("%s, ", (char *) btree_get_value(tree, index));
        print_inorden(tree, btree_get_rchild(index));
    }
}

char *
get_num(char **expr)
{
    char *ret = *expr;
    while ('0' <= **expr && **expr <= '9')
    {
        ++expr;
    }
    return *expr - ret == 0 ? NULL : ret;
}

BTree
analize(char *expr)
{
    BTree etree;
    BTree temptree;
    Stack op_stack;
    Stack num_stack;
    char *num;
    char *top_op;
    char *top_n;
    char  op;


    etree    = btree_create(strlen(expr));
    temptree = btree_create(strlen(expr));

    stack_init();
    stack_new(&num_stack, strlen(expr), typeof(top_op));
    stack_new(&op_stack, strlen(expr), typeof(top_n));

    while (*expr != '\0')
    {
        if ((num = get_num(&expr)))
            stack_add(&num_stack, num);

        else if (stack_get_top(op_stack, &top_op) == STACK_EMPTY)
        {
            stack_add(&op_stack, &top_op);
            ++expr;
        }
        else if (stack_get_top(op_stack, &top_op),
                 PRIORITY[*(int *) top_op] < PRIORITY[(int) *expr])
        {
            stack_add(&op_stack, &top_op);
            ++expr;
        }
        else // expr is op and top has more priority
        {
            op = *expr;
            ++expr;
            temptree = btree_create(2);
            num      = get_num(&expr);
            stack_get_top(num_stack, &top_n);
            btree_set_value(&temptree, btree_get_root(), USEPRM op);
            btree_set_value(&temptree, btree_get_lchild(btree_get_root()), USEPRM num);
            btree_set_value(&temptree, btree_get_rchild(btree_get_root()), USEPRM top_n);
        }
    }
    return etree;
}

int
main(int argc, char *argv[])
{
    BTree etree;
    if (argc == 2)
    {
        etree = analize(argv[1]);
        btree_repr(etree, "s", char *);
        btree_delete(&etree);
    }
    else
    {
        etree = analize("");
        btree_repr(etree, "s", char *);
        btree_delete(&etree);
    }
    return 0;
}
