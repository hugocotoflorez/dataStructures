#include "hash.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int
get_index(const char *key, int size)
{
    int i = 0;
    while (*key != '\0')
    {
        i += *key;
        ++key;
        i %= size;
    }
    return i;
}

Hash
hash_create(int size)
{
    Hash h = (Hash){
        .size  = size,
        .table = calloc(size, sizeof(hash_t)),
    };
    assert(h.table != NULL);

    return h;
}

void
hash_destroy(Hash *hash)
{
    for (int i = 0; i < hash->size; i++)
    {
        hash_t *temp = hash->table[i].next;
        while (temp != NULL)
        {
            hash_t *to_free = temp;
            temp            = temp->next;
            free(to_free);
        }
    }
    free(hash->table);
    hash->table = NULL;
    hash->size  = 0;
}

void
hash_add(Hash hash, const char *key, VAL_T value)
{
    int     index = get_index(key, hash.size);
    hash_t *newnode, *temp;

    if (hash.table[index].key[0] == '\0')
    {
        newnode = hash.table + index;
    }
    else
    {
        newnode = malloc(sizeof(hash_t));
        temp    = hash.table + index;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newnode;
    }

    strcpy(newnode->key, key);
    newnode->next  = NULL;
    newnode->value = value;
}

VAL_T
hash_search(Hash hash, const char *key)
{
    int     index = get_index(key, hash.size);
    hash_t *temp  = hash.table + index;
    while (temp != NULL && strcmp(temp->key, key) != 0)
        temp = temp->next;

    return (temp != NULL) ? temp->value : ERRVAL;
}

VAL_T
hash_remove(Hash hash, const char *key)
{
    int     index = get_index(key, hash.size);
    hash_t *temp  = hash.table + index;
    hash_t *prev  = NULL;

    while (temp != NULL && strcmp(temp->key, key) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return ERRVAL; // Key not found
    }

    VAL_T removed_value = temp->value;

    if (prev == NULL)
    {
        // The element to be removed is the first in the bucket
        if (temp->next == NULL)
        {
            // If the element is the only one in the list
            temp->key[0] = '\0';
        }
        else
        {
            // Move the next element to the current spot
            hash_t *next = temp->next;
            *temp        = *next;
            free(next);
        }
    }
    else
    {
        prev->next = temp->next;
        free(temp);
    }

    return removed_value;
}
