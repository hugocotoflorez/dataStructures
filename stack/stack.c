#include "stack.h"
#include <stdio.h>

int
main()
{
    STACK stack;
    int   size = 10;
    int   element;
    stack_init();
    stack_new(&stack, size, element);
    stack_add(&stack, (int) 10);
    stack_add(&stack, (int) 14);
    stack_pop(&stack, &element);
    printf("Pop %d\n", element);
    stack_get_top(stack, &element);
    return 0;
}
