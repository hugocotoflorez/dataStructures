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

#define stack_init() void *new_stack;

#define stack_new(stackptr, size, typed_var)                                     \
    ((new_stack = malloc(sizeof(typeof(typed_var)) * (size))),                   \
     (new_stack == NULL) ?                                                       \
     STACK_ALLOC_ERROR :                                                         \
     ((*(stackptr) = (STACK){ new_stack, new_stack,                              \
                              new_stack + (size) * sizeof(typeof(typed_var)) }), \
      STACK_NOERROR))

#define stack_free(stackptr)     \
    {                            \
        free((stackptr)->stack); \
        stackptr->stack = NULL;  \
    }

#define stack_add(stackptr, element)                            \
    (((stackptr)->stack_ptr == (stackptr)->stack_end) ?         \
     STACK_FULL :                                               \
     ((*(typeof(element) *) (stackptr)->stack_ptr = (element)), \
      ((stackptr)->stack_ptr += sizeof(typeof(element))), STACK_NOERROR))

#define stack_pop(stackptr, pop_elem_ptr)                 \
    (((stackptr)->stack_ptr == (stackptr)->stack) ?       \
     STACK_EMPTY :                                        \
     (((stackptr)->stack_ptr -= sizeof(typeof(element))), \
      (*(pop_elem_ptr) = *(typeof(element) *) (stackptr)->stack_ptr), STACK_NOERROR))

#define stack_get_top(stack, top_element_ptr)                                \
    (((stack).stack_ptr == (stack).stack) ?                                  \
     STACK_EMPTY :                                                           \
     (*(top_element_ptr) = *((typeof((top_element_ptr))) (stack).stack_ptr - \
                             1),\
                             STACK_NOERROR))


#endif // _STACK_H