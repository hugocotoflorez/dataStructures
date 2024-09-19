#include "linkedlist.h"
#include <stdlib.h>

/*
List_node list_next_node(List_node n);
void list_delete(Linked_list* l);
size_t list_length(Linked_list* l);
// extend l1 with l2. L2 wont be modified
void list_extend(Linked_list* l1, Linked_list l2);
 */

Linked_list
list_new()
{
    return (Linked_list){
        .head   = NULL,
        .tail   = NULL,
        .length = 0,
    };
}


void
list_append(Linked_list *l, element_t e)
{
    List_node *new_node = malloc(sizeof(List_node));

    *new_node = (List_node){
        .next    = NULL,
        .element = e,
    };
    if (l->length == 0)
    {
        l->head = new_node;
    }
    l->tail->next = new_node;
    l->tail       = new_node;
    l->length++;
}


void
list_insert(Linked_list *l, List_node *n, element_t e)
{
    List_node *new_node = malloc(sizeof(List_node));

    *new_node = (List_node){
        .next    = n->next,
        .element = e,
    };
    n->next = new_node;
    if (new_node->next == NULL)
        l->tail = new_node;
    l->length++;
}


void
list_head_append(Linked_list *l, element_t e)
{
    List_node *new_node = malloc(sizeof(List_node));

    *new_node = (List_node){
        .next    = l->head,
        .element = e,
    };
    if (l->length == 0)
    {
        l->tail = new_node;
    }
    l->head = new_node;
    l->length++;
}
