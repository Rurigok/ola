#ifndef OLA_DEQUE_H
#define OLA_DEQUE_H

#define DEFAULT_deque_ALLOC_SIZE 10
#define deque_ALLOC_SIZE_MULTIPLIER 2

typedef struct deque {
    void **valArray;
    unsigned int size;
    int maxPopIndex;
    unsigned int allocSize;
} deque;

deque * createDeque();                        // create a new double-ended queue
void dequeAdd(deque *deque, void *value);     // add value to end
void dequeShift(deque *deque, void *value);   // add value to front
void * dequeUnshift(deque *deque);            // remove and return value at front
void dequePush(deque *deque, void *value);    // add value to end
void * dequePop(deque *deque);                // remove and return value at end
void * dequePeek(deque *deque);               // get last value
void * dequeGet(deque *deque, int index);     // get value at index
void * dequeRemove(deque *deque, int index);  // remove and return value at index
void dequeClear(deque *deque);                // remove all elements
void dequeError(const char *message);

#endif // OLA_DEQUE_H
