#ifndef OLA_HASHTABLE_H
#define OLA_HASHTABLE_H

typedef struct entry_s {
    void *key               // keys may be anything
    void *value             // values may be anything
    struct entry_s *next;
} entry_t;

typedef struct hashtable_s {
    int size;
    struct entry_t **table;
} hashtable_t;

hashtable * ht_create(int size);            // create a new hashtable

#endif //OLA_HASHTABLE_H
