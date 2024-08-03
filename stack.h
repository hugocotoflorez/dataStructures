#ifndef _STACK_H
#define _STACK_H

#include <stddef.h> // size_t
#include <stdlib.h> // malloc & free

typedef enum
{
    STACK_NOERROR = 0,
    STACK_FULL,
    STACK_EMPTY,
    STACK_ALLOC_ERROR,
} STACK_ERR;

typedef struct
{
    void *stack;     // apunta al primer elemento
    void *stack_ptr; // apunta al siguiente elemento
    void *stack_end; // apunta al ultimo elemento
} STACK;


#define INIT_STACK(type)                                                           \
    STACK_ERR stack_new_##type(STACK *stack, size_t size)                          \
    {                                                                              \
        void *new_stack = malloc(sizeof(type) * size);                             \
        if (new_stack == NULL)                                                     \
            return STACK_ALLOC_ERROR;                                              \
        *stack = (STACK){ new_stack, new_stack, new_stack + size * sizeof(type) }; \
        return STACK_NOERROR;                                                      \
    }                                                                              \
                                                                                   \
    void stack_free_##type(STACK *stack)                                           \
    {                                                                              \
        free(stack->stack);                                                        \
        stack->stack = NULL;                                                       \
    }                                                                              \
                                                                                   \
    STACK_ERR stack_add_##type(STACK *stack, type element)                         \
    {                                                                              \
        if (stack->stack_ptr == stack->stack_end)                                  \
            return STACK_FULL;                                                     \
        *(type *) stack->stack_ptr = element;                                      \
        stack->stack_ptr += sizeof(type);                                          \
        return STACK_NOERROR;                                                      \
    }                                                                              \
                                                                                   \
    STACK_ERR stack_pop_##type(STACK *stack, type *pop_element)                    \
    {                                                                              \
        if (stack->stack_ptr == stack->stack)                                      \
            return STACK_EMPTY;                                                    \
        stack->stack_ptr -= sizeof(type);                                          \
        *pop_element = *(type *) stack->stack_ptr;                                 \
        return STACK_NOERROR;                                                      \
    }                                                                              \
                                                                                   \
    STACK_ERR stack_get_top_##type(STACK stack, type *top_element)                 \
    {                                                                              \
        if (stack.stack_ptr == stack.stack)                                        \
            return STACK_EMPTY;                                                    \
        *top_element = *((type *) stack.stack_ptr - sizeof(type));                 \
        return STACK_NOERROR;                                                      \
    }

#endif // _STACK_H
