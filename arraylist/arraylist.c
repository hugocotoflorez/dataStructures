#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

// Where is .h? idk

#define AL_INCREMENT 2;
#define ELEM_ERR 0;
// type declarations
typedef int element_t;
typedef struct __araylist
{
    element_t **data;

    size_t capacity;
    size_t length;


} Arraylist;

// ---------- function declarations ---------- //
// create a list
Arraylist arraylist_create(size_t capacity);
// modify the element in a valid index
void arraylist_modify(Arraylist *arraylist, size_t index, element_t element);
// append an element to the end of the list
size_t arraylist_append(Arraylist *arraylist, element_t element);
// insert an element at index (quite inefficient)
void arraylist_insert(Arraylist *arraylist, size_t index, element_t element);
// remove an element at index
element_t arraylist_remove(Arraylist *arraylist, size_t index);
// get the element at some index
element_t arraylist_get(Arraylist arraylist, size_t index);
// just for 'debugging'
void arraylist_print(Arraylist arraylist);


Arraylist
arraylist_create(size_t capacity)
{
    return (Arraylist){
        .capacity = capacity > 0 ? capacity : 1,
        .length   = 0,
        .data     = malloc(sizeof(element_t *) * capacity),
    };
}

void
_arraylist_resize(Arraylist *arraylist)
{
    arraylist->capacity *= AL_INCREMENT;
    arraylist->data =
    realloc(arraylist->data, arraylist->capacity * sizeof(element_t *));
}

size_t
arraylist_append(Arraylist *arraylist, element_t element)
{
    if (arraylist->length == arraylist->capacity)
        _arraylist_resize(arraylist);
    arraylist->data[arraylist->length]    = malloc(sizeof(element_t));
    *(arraylist->data[arraylist->length]) = element;
    return arraylist->length++;
}

void
arraylist_modify(Arraylist *arraylist, size_t index, element_t element)
{
    if (index >= arraylist->length)
        return;
    *(arraylist->data[index]) = element;
}

// i and j MUST be 0<=i,j<length
void
_swap(Arraylist *arraylist, size_t i, size_t j)
{
    element_t *temp    = arraylist->data[i];
    arraylist->data[i] = arraylist->data[j];
    arraylist->data[j] = temp;
}

void
arraylist_insert(Arraylist *arraylist, size_t index, element_t element)
{
    if (index >= arraylist->length)
        return;
    arraylist_append(arraylist, element);
    for (int i = arraylist->length - 1; i > index; i--)
        _swap(arraylist, i, i - 1);
}


element_t
arraylist_remove(Arraylist *arraylist, size_t index)
{
    element_t temp;
    if (index >= arraylist->length)
        return ELEM_ERR;
    temp = arraylist_get(*arraylist, index);
    free(arraylist->data[index]);
    for (int i = index; i < arraylist->length; i++)
    {
        arraylist->data[i] = arraylist->data[i + 1];
    }
    --arraylist->length;
    return temp;
}


element_t
arraylist_get(Arraylist arraylist, size_t index)
{
    if (index >= arraylist.length)
        return ELEM_ERR;
    return *((element_t *) arraylist.data[index]);
}

void
arraylist_print(Arraylist arraylist)
{
    for (int i = 0; i < arraylist.length; i++)
        printf("%d, ", arraylist_get(arraylist, i));
    putchar('\n');
}


#ifdef TEST

int
main(void)
{
    Arraylist arr;
    puts("Creating");
    arr = arraylist_create(1);
    arraylist_print(arr);
    puts("Appending");
    arraylist_append(&arr, 3);
    arraylist_append(&arr, 5);
    arraylist_append(&arr, 6);
    arraylist_append(&arr, 7);
    arraylist_append(&arr, 8);
    arraylist_print(arr);
    puts("Inserting");
    arraylist_insert(&arr, 2, 9);
    arraylist_insert(&arr, 0, 10);
    arraylist_insert(&arr, 10, 10);
    arraylist_print(arr);
    puts("Modifying");
    arraylist_modify(&arr, 0, 1);
    arraylist_modify(&arr, 4, 2);
    arraylist_print(arr);
    puts("Removing");
    arraylist_remove(&arr, 0);
    arraylist_remove(&arr, 4);
    arraylist_remove(&arr, 10);
    arraylist_print(arr);
}
#endif
