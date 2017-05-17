#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"

int main(int argc, char *argv[]) {

    hashtable_t *ht = ht_create(10);

    char *key1 = "myStr";
    char *key2 = "x";

    char *val1 = "hello world!";
    int val2 = 7;

    ht_put(ht, key1, 6, val1);
    ht_put(ht, key2, 2, &val2);

    char *getVal1 = ht_get(ht, key1, 6);
    int *getVal2 = ht_get(ht, key2, 2);

    printf("%s = %s\n", key1, getVal1);
    printf("%s = %d\n", key2, *getVal2);

    return 0;

}
