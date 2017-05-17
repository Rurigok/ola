//
// Created by andrew on 5/12/17.
//

#include <stdlib.h>

#include "error.h"
#include "hashtable.h"

unsigned int hashfunc(void *key, unsigned int keySize, unsigned int tableSize) {
    unsigned int digest, x;
    unsigned int *keyVal;
    
    keyVal = (unsigned int *)key;
    
    /* multiplication method of hashing */
    digest = 0;
    for (x = 0; x < keySize; x++)
        digest = digest * MULTIPLIER + keyVal[x];
    
    return digest % tableSize;
}

hashtable_t * ht_create(int size) {

    if (size < 1)
        return NULL;

    hashtable_t *ht = NULL;

    /* memalloc table */
    if ((ht = calloc(sizeof(hashtable_t), 1)) == NULL)
        return NULL;
    
    /* memalloc entries */
    if ((ht -> table = calloc(size, sizeof(entry_t*))) == NULL)
        return NULL;
    
    ht -> size = size;
    
    return ht;
}

// TODO: ht_rehash

void ht_put(hashtable_t *ht, void *key, unsigned int keySize, void *value) {

    if (ht == NULL)
        internalError("Attempt to put into uninitialized hash table");

    if (key == NULL)
        internalError("Attempt to put null key into hash table");

    if (value == NULL)
        internalError("Attempt to insert invalid value pointer into hash table");

    unsigned int hashKey = hashfunc(key, keySize, ht -> size);

    if (ht->table[hashKey] == NULL) {
        // Slot is empty. Add a new entry here

        entry_t *newEntry = malloc(sizeof(entry_t));

        if (newEntry == NULL)
            sysError("malloc failed to create ht entry");

        newEntry->key = key;
        newEntry->keySize = keySize;
        newEntry->value = value;
        newEntry->next = NULL;

    } else {
        // Collision! Add new entry at the end of the chain

        entry_t *cur = ht->table[hashKey];

        while (cur->next != NULL) {
            cur = cur->next;
        }
        // cur is now the last entry_t in the chain

        entry_t *newEntry = malloc(sizeof(entry_t));

        if (newEntry == NULL)
            sysError("malloc failed to create ht entry");

        newEntry->key = key;
        newEntry->keySize = keySize;
        newEntry->value = value;
        newEntry->next = NULL;

        cur->next = newEntry;

    }

}

void * ht_get(hashtable_t *ht, void *key, unsigned int keySize) {

    if (ht == NULL)
        internalError("Attempt to get from uninitialized hash table");

    if (key == NULL)
        internalError("Attempt to get null key into hash table");

    unsigned int hashKey = hashfunc(key, keySize, ht -> size);

    entry_t *found = ht->table[hashKey];

    while (found != NULL) {

        if (found->keySize == keySize && memcmp(found->key, key, keySize) == 0) {
            return found->value;
        }

        found = found->next;

    }

    if (found == NULL)
        // Did not find the given key
        return NULL;

}

// TODO: ht_remove

// TODO: ht_clear
