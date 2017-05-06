#include <stdio.h>
#include <stdlib.h>
#include "list.h"

deque * createList() {

    deque *newList = (deque *) malloc(sizeof(deque));

    newList->size = 0;
    newList->maxPopIndex = -1;
    newList->valArray = (void **) calloc(sizeof(void *), DEFAULT_LIST_ALLOC_SIZE);
    newList->allocSize = DEFAULT_LIST_ALLOC_SIZE;

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
        list->valArray = (void **) realloc(list->valArray, sizeof(void *) * list->allocSize * LIST_ALLOC_SIZE_MULTIPLIER);
        list->allocSize = list->allocSize * LIST_ALLOC_SIZE_MULTIPLIER;
    }

    list->maxPopIndex++;
    list->valArray[list->maxPopIndex] = value;
    list->size++;

}

void * listPop(deque *list) {
    return NULL;
}

void * listGet(deque *list, int index) {
    return NULL;
}

void * listRemove(deque *list, int index) {
    return NULL;
}

void listClear(deque *list) {

}

void listError(const char *message) {
    fprintf(stderr, "Internal list error: %s\n", message);
    exit(EXIT_FAILURE);
}
