#ifndef OLA_LIST_IMPL_H
#define OLA_LIST_IMPL_H

#define DEFAULT_LIST_ALLOC_SIZE 10
#define LIST_ALLOC_SIZE_MULTIPLIER 2

typedef struct deque {
    void **valArray;
    unsigned int size;
    int maxPopIndex;
    unsigned int allocSize;
} deque;

deque * createList();                       // create a new double-ended queue
void listAdd(deque *list, void *value);     // add value to end
void listShift(deque *list, void *value);   // add value to front
void * listUnshift(deque *list);            // remove and return value at front
void listPush(deque *list, void *value);    // add value to end
void * listPop(deque *list);                // remove and return value at end
void * listGet(deque *list, int index);     // get value at index
void * listRemove(deque *list, int index);  // remove and return value at index
void listClear(deque *list);                // remove all elements
void listError(const char *message);

#endif
