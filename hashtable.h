#ifndef OLA_HASHTABLE_H
#define OLA_HASHTABLE_H

#define MULTIPLIER (37)     // by convention

typedef struct entry_s {
    void *key;              // keys may be anything
    unsigned int keySize;   // bytes of key
    void *value;            // values may be anything
    struct entry_s *next;   // next entry in chain
} entry_t;

typedef struct hashtable_s {
    int size;
    struct entry_t *table[];
} hashtable_t;

unsigned int hashfunc(void *key, unsigned int keySize, unsigned int tableSize); // create a hash value from key
hashtable_t * ht_create(int size);                                              // create a new hashtable
hashtable_t * ht_rehash(hashtable_t *ht);                                       // returns a new hashtable when size met
void ht_put(hashtable_t *ht, void *key, unsigned int keySize, void *value);     // put key/value pair into hash table
void * ht_get(hashtable_t *ht, void *key, unsigned int keySize);                // get value by key
void * ht_remove(hashtable_t *ht, void *key, unsigned int keySize);             // remove key/value pair by key
void ht_clear(hashtable_t *ht);                                                 // delete all keys and values

#endif //OLA_HASHTABLE_H
