#ifndef _HASH_H
#define _HASH_H


#define KEYLEN 20
#define ERRVAL (~(0))

typedef int VAL_T;


typedef struct __hash_t
{
    struct __hash_t *next;
    char             key[KEYLEN];
    VAL_T            value;
} hash_t;

typedef struct
{
    hash_t *table;
    int     size;
} Hash;


Hash hash_create(int size);
void hash_destroy(Hash *hash);

void  hash_add(Hash hash, const char *key, VAL_T value);
VAL_T hash_search(Hash hash, const char *key);
VAL_T hash_remove(Hash hash, const char *key);


#endif
