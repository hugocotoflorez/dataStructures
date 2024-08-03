#include "hash.h"
#include <stdio.h>

void
hash_print(Hash h)
{
    puts("----------------");
    for (int i = 0; i < h.size; i++)
    {
        for (hash_t *temp = h.table + i; temp != NULL; temp = temp->next)
            printf("%s : %d -> ", temp->key, temp->value);
        puts("");
        puts("----------------");
    }
}

int
main()
{
    Hash h = hash_create(1);
    hash_add(h, "Hugo", 1);
    hash_add(h, "Coto", 1);
    hash_add(h, "Florez", 1);
    hash_add(h, "H", 1);
    hash_add(h, "C", 123456);
    hash_add(h, "F", 1);
    hash_remove(h, "Hugo");
    hash_remove(h, "F");
    hash_print(h);
    printf("Value at %s: %d\n", "C", hash_search(h, "C"));
    hash_destroy(&h);

    return 0;
}
