#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"
#include "error.h"

deque * createDeque() {

    deque *newDeque = (deque *) malloc(sizeof(deque));

    if (newDeque == NULL) {
        sysError("malloc");
    }

    newDeque->size = 0;
    newDeque->maxPopIndex = -1;
    newDeque->valArray = (void **) calloc(sizeof(void *), DEFAULT_deque_ALLOC_SIZE);
    newDeque->allocSize = DEFAULT_deque_ALLOC_SIZE;

    if (newDeque->valArray == NULL) {
        sysError("calloc");
    }

    return newDeque;

}

void dequeAdd(deque *deque, void *value) {
    dequePush(deque, value);
}

void dequeShift(deque *deque, void *value) {

}

void * dequeUnshift(deque *deque) {
    return NULL;
}

void dequePush(deque *deque, void *value) {

    if (deque == NULL) {
        dequeError("push to uninitialized deque");
    }

    if (deque->size >= deque->allocSize) {
        // TODO: assign realloc to temp var to check for NULL and prevent memory leak
        deque->valArray = (void **) realloc(deque->valArray, sizeof(void *) * deque->allocSize * deque_ALLOC_SIZE_MULTIPLIER);
        deque->allocSize = deque->allocSize * deque_ALLOC_SIZE_MULTIPLIER;
    }

    deque->maxPopIndex++;
    deque->valArray[deque->maxPopIndex] = value;
    deque->size++;

}

void * dequePop(deque *deque) {

    if (deque == NULL) {
        dequeError("pop from uninitialized deque");
    }

    if (deque->size == 0) {
        return NULL;
    }

    void *poppedValue = deque->valArray[deque->maxPopIndex];

    deque->valArray[deque->maxPopIndex] = NULL;
    deque->size--;
    deque->maxPopIndex--;

    return poppedValue;

}

void * dequePeek(deque *deque) {

    return dequeGet(deque, deque->maxPopIndex);

}

void * dequeGet(deque *deque, int index) {

    if (deque == NULL) {
        dequeError("get from uninitialized deque");
    }

    if (deque->size <= 0 || index > deque->maxPopIndex) {
        return NULL;
    }

    return deque->valArray[index];

}

void * dequeRemove(deque *deque, int index) {

    if (deque == NULL) {
        dequeError("remove from uninitialized deque");
    }

    if (deque->size <= 0 || index > deque->maxPopIndex) {
        return NULL;
    }

    void *removedValue = deque->valArray[index];

    memmove(&deque->valArray[index], &deque->valArray[index + 1], sizeof(void *) * (deque->maxPopIndex - index));

    deque->size--;
    deque->maxPopIndex--;

    return removedValue;

}

void dequeClear(deque *deque) {

    if (deque == NULL) {
        dequeError("clear uninitialized deque");
    }

    while (deque->size > 0) {
        dequeRemove(deque, 0);
    }

}

void dequeError(const char *message) {
    fprintf(stderr, "Internal deque error: %s\n", message);
    exit(EXIT_FAILURE);
}
