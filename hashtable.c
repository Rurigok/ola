//
// Created by andrew on 5/12/17.
//

#include <stdlib.h>
#include "hashtable.h"

hashtable * ht_create(int size)
{
    hashtable *ht = NULL;
    int x;
    
    if (size < 1)
        return NULL;
    
    /* memalloc table */
    if ((ht -> table = malloc(sizeof(hashtable))) == NULL)
        return NULL;
    
    /* memalloc entries */
    if ((ht -> table = malloc(sizeof(entry *) * size)) == NULL)
        return NULL;
    for (x = 0; x < size; x++)
        ht -> table[x] = NULL;
    
    ht -> size = size;
    
    return ht;
}
