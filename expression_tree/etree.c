#include "btree.h"
#include "stack.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int PRIORITY[] = {
    ['+'] = 1, ['-'] = 1, ['*'] = 2, ['/'] = 2,
    ['^'] = 3, ['('] = 0, [')'] = 4,
};

inline static int
is_num(char c)
{
    return '0' <= c && c <= '9';
}

char *
strnum(int n)
{
    char *buf = malloc(10);
    sprintf(buf, "%d", n);
    return buf;
}

/* Get the num starting at *buffer and move buffer to next token
 * if prev buffer == current buffer, char at buffer is not a number*/
static int
get_num(char **buffer)
{
    int n = 0;
    while (is_num(**buffer))
    {
        n *= 10;
        n += **buffer - '0';
        ++*buffer;
    }
    return n;
}

BTree *
analize(char *expr)
{
    char      top_op;          // operator at stack top
    BTree    *temp_tree;       // used for creating trees
    BTree    *subtree;         // used for merging trees
    STACK     stack_operands;  // stack for num or sub-expression-tree
    STACK     stack_operators; // stack for operators
    STACK_ERR status;          // stack operations status
    char      buf[1];          // store operators

    // create aux stack for nums and operators
    stack_init();
    stack_new(&stack_operands, strlen(expr), subtree);
    stack_new(&stack_operators, strlen(expr), char);

    // start analizer
    while (*expr) // until expr == '\0'
    {
        // jump over spaces
        if (*expr == ' ')
        {
            ++*expr;
            continue;
        }

        // current element is a number
        if (is_num(*expr))
        {
            temp_tree = btree_empty();
            btree_set_value(temp_tree, strnum(get_num(&expr))); // GNU c !
            assert(stack_add(&stack_operands, temp_tree) == STACK_NOERROR);
        }

        // current element is an operator
        else
        {
            // top of operators stack
            status = stack_get_top(stack_operators, &top_op);

            // if operators stack is empty, add to stack
            if (status == STACK_EMPTY)
                stack_add(&stack_operators, *expr);

            // stack is not empty
            else
            {
                // create subtree until '('
                if (*expr == ')')
                    while (*expr != '(' && stack_get_top(stack_operators, &top_op) != STACK_EMPTY)
                    {
                        ++expr;
                    }
                // if new priority <= last, add to stack
                else if (PRIORITY[(int) *expr] <= PRIORITY[(int) top_op])
                    stack_add(&stack_operators, *expr);

                // new priority is greater

                else
                {
                    buf[0] = *expr;
                    // create new tree with root value operator
                    temp_tree = btree_empty();
                    btree_set_value(temp_tree, strdup(buf)); // GNU c !
                    // remove from stack and add to tree as right child
                    assert(stack_pop(&stack_operands, &subtree) == STACK_NOERROR);
                    btree_extend_rchild(temp_tree, subtree);
                    // remove from stack and add to tree as left child
                    assert(stack_pop(&stack_operands, &subtree) == STACK_NOERROR);
                    btree_extend_lchild(temp_tree, subtree);
                    // add temp tree to stack
                    assert(stack_add(&stack_operands, temp_tree) == STACK_NOERROR);
                }
            }
            // move expression string cursor
            ++expr;
        }
    }
    temp_tree = NULL;
    while (stack_get_top(stack_operators, &subtree) != STACK_EMPTY)
    {
        temp_tree = btree_empty();
        // remove from stack and set as root value
        assert(stack_pop(&stack_operators, &top_op) == STACK_NOERROR);
        buf[0] = top_op;
        btree_set_value(temp_tree, strdup(buf)); // GNU C !

        // remove from stack and add to tree as right child
        assert(stack_pop(&stack_operands, &subtree) == STACK_NOERROR);
        btree_extend_rchild(temp_tree, subtree);
        // remove from stack and add to tree as left child
        assert(stack_pop(&stack_operands, &subtree) == STACK_NOERROR);
        btree_extend_lchild(temp_tree, subtree);
        // add temp tree to stack
        assert(stack_add(&stack_operands, temp_tree) == STACK_NOERROR);
    }
    // assert(stack_pop(&stack_operands, &temp_tree) == STACK_NOERROR);
    return temp_tree;
}

void
print_inorden(BTree *tree)
{
    if (tree == NULL)
        return;
    print_inorden(tree->lchild);
    printf("%s ", (char *) btree_get_value(*tree));
    print_inorden(tree->rchild);
}

int
main(int argc, char *argv[])
{
    BTree *tree;
    if (argc == 2)
    {
        tree = analize(argv[1]);
        print_inorden(tree);
        btree_delete_tree(tree);
    }
    else
    {
        tree = analize("2+3*5-1/4");
        print_inorden(tree);
        btree_delete_tree(tree);
    }
    printf("\n");
    return 0;
}
