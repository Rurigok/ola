
typedef struct listNode {
    struct listNode *next;
    struct listNode *prev;
    void *value;
} listNode;

typedef struct llist {
    struct listNode *head;
    struct listNode *tail;
    int size;
} llist;

llist * createList();                        // create a new linked list
void listAdd(llist *list, void *value);     // add value to end
void listShift(llist *list, void *value);   // add value to front
void * listUnshift(llist *list);            // remove and return value at front
void listPush(llist *list, void *value);    // add value to end
void * listPop(llist *list);                // remove and return value at end
void * listGet(llist *list, int index);     // get value at index
void * listRemove(llist *list, int index);  // remove and return value at index
void listClear(llist *list);                // remove all elements
