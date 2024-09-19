#include "stack.h"
#include <stdio.h>

int
main()
{
    STACK     stack;
    int       size = 1;
    int       element;
    int       val1 = 14;
    int       val2 = 10;
    STACK_ERR status;
    stack_init();
    stack_new(&stack, size, int);

    status = stack_add(&stack, val1);
    printf("[%s] Add %d\n", stackErrStr[status], val1);

    status = stack_add(&stack, val1);
    printf("[%s] Add %d\n", stackErrStr[status], val1);

    status = stack_get_top(stack, &element);
    printf("[%s] Top %d\n", stackErrStr[status], element);

    status = stack_add(&stack, val2);
    printf("[%s] Add %d\n", stackErrStr[status], val2);

    status = stack_get_top(stack, &element);
    printf("[%s] Top %d\n", stackErrStr[status], element);

    status = stack_pop(&stack, &element);
    printf("[%s] Pop %d\n", stackErrStr[status], element);

    status = stack_get_top(stack, &element);
    printf("[%s] Top %d\n", stackErrStr[status], element);

    status = stack_pop(&stack, &element);
    printf("[%s] Pop %d\n", stackErrStr[status], element);


    stack_destroy(stack);

    return 0;
}
