#ifndef OLA_HASHTABLE_H
#define OLA_HASHTABLE_H

typedef struct entry_s {
    void *key;              // keys may be anything
    unsigned int keySize;
    void *value;            // values may be anything
    struct entry_s *next;
} entry_t;

typedef struct hashtable_s {
    int size;
    struct entry_t *table[];
} hashtable_t;

hashtable_t * ht_create(int size);                      // create a new hashtable
void ht_put(hashtable_t *ht, void *key, unsigned int keySize, void *value);   // put key/value pair into hash table
void * ht_get(hashtable_t *ht, void *key, unsigned int keySize);              // get value by key
void * ht_remove(hashtable_t *ht, void *key, unsigned int keySize);           // remove key/value pair by key
void ht_clear(hashtable_t *ht);                         // delete all keys and values

#endif //OLA_HASHTABLE_H
