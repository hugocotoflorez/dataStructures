
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stddef.h>

// element stored into each node
typedef int element_t;

// list node, points to next node and
// store current node value
typedef struct __list_node
{
    struct __list_node* next;
    element_t element;
} List_node;

// base type for the list
typedef struct __list
{
    List_node *head, *tail;
    size_t length;
} Linked_list;


Linked_list list_new();
void list_append(Linked_list* l, element_t e);
void list_insert(Linked_list* l, List_node* n, element_t e);
element_t list_pop(Linked_list* l, List_node* n);
List_node list_next_node(List_node n);
void list_delete(Linked_list* l);
size_t list_length(Linked_list* l);
// extend l1 with l2. L2 wont be modified
void list_extend(Linked_list* l1, Linked_list l2);


#endif // !_LINKED_LIST_H
