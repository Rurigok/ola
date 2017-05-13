#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"
#include "error.h"

deque * createList() {

    deque *newList = (deque *) malloc(sizeof(deque));

    if (newList == NULL) {
        sysError("malloc");
    }

    newList->size = 0;
    newList->maxPopIndex = -1;
    newList->valArray = (void **) calloc(sizeof(void *), DEFAULT_LIST_ALLOC_SIZE);
    newList->allocSize = DEFAULT_LIST_ALLOC_SIZE;

    if (newList->valArray == NULL) {
        sysError("calloc");
    }

    return newList;

}

void listAdd(deque *list, void *value) {
    listPush(list, value);
}

void listShift(deque *list, void *value) {

}

void * listUnshift(deque *list) {
    return NULL;
}

void listPush(deque *list, void *value) {

    if (list == NULL) {
        listError("push to uninitialized list");
    }

    if (list->size >= list->allocSize) {
        // TODO: assign realloc to temp var to check for NULL and prevent memory leak
        list->valArray = (void **) realloc(list->valArray, sizeof(void *) * list->allocSize * LIST_ALLOC_SIZE_MULTIPLIER);
        list->allocSize = list->allocSize * LIST_ALLOC_SIZE_MULTIPLIER;
    }

    list->maxPopIndex++;
    list->valArray[list->maxPopIndex] = value;
    list->size++;

}

void * listPop(deque *list) {

    if (list == NULL) {
        listError("pop from uninitialized list");
    }

    if (list->size == 0) {
        return NULL;
    }

    void *poppedValue = list->valArray[list->maxPopIndex];

    list->valArray[list->maxPopIndex] = NULL;
    list->size--;
    list->maxPopIndex--;

    return poppedValue;

}

void * listGet(deque *list, int index) {

    if (list == NULL) {
        listError("get from uninitialized list");
    }

    if (list->size <= 0 || index > list->maxPopIndex) {
        return NULL;
    }

    return list->valArray[index];

}

void * listRemove(deque *list, int index) {

    if (list == NULL) {
        listError("remove from uninitialized list");
    }

    if (list->size <= 0 || index > list->maxPopIndex) {
        return NULL;
    }

    void *removedValue = list->valArray[index];

    memmove(&list->valArray[index], &list->valArray[index + 1], sizeof(void *) * (list->maxPopIndex - index));

    list->size--;
    list->maxPopIndex--;

    return removedValue;

}

void listClear(deque *list) {

}

void listError(const char *message) {
    fprintf(stderr, "Internal list error: %s\n", message);
    exit(EXIT_FAILURE);
}
