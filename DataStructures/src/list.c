#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct element element;
struct element {
    element * next, * prev;
};

struct ds_list {
    size_t typeSize, size;
    element * front, * end;
};

inline ds_list * dsList(size_t const typeSize) {
    element * const end = malloc(sizeof(element));
    *end = (element) { .next = 0, .prev = 0 };
    ds_list * const list = malloc(sizeof(ds_list));
    *list = (ds_list) { .typeSize = typeSize, .size = 0, .front = end, .end = end };
    return list;
}

ds_list * dsListCopy(ds_list const * const src) {
    ds_list * list = dsList(src->typeSize);
    for(element const * iter = src->front; iter->next; iter = iter->next)
        memcpy(dsListAt(dsListPushBack(list)), dsListAt(iter), list->typeSize);
    return list;
}

inline void dsListDelete(ds_list * const list) {
    dsListClear(list);
    free(list);
}

inline void * dsListAt(void const * const pos) {
    return (element *) pos + 1;
}

inline void * dsListNext(void const * const pos) {
    return ((element *) pos)->next;
}

inline void * dsListPrev(void const * const pos) {
    return ((element *) pos)->prev;
}

inline void * dsListFront(ds_list const * const list) {
    return list->front;
}

inline void * dsListBack(ds_list const * const list) {
    return list->end->prev;
}

inline void * dsListEnd(ds_list const * const list) {
    return list->end;
}

inline size_t dsListSize(ds_list const * const list) {
    return list->size;
}

void dsListClear(ds_list * const list) {
    element * iter = list->front;
    while(iter->next) {
        element * const next = iter->next;
        free(iter);
        iter = next;
    }
    iter->prev = 0;
}

inline void * dsListInsert(ds_list * const list, void * const pos) {
    element * const newElement = malloc(sizeof(element) + list->typeSize);
    *newElement = (element) { .next = pos, .prev = ((element *) pos)->prev };
    if(newElement->prev)
        newElement->prev->next = newElement;
    else
        list->front = newElement;
    ((element *) pos)->prev = newElement;
    list->size++;
    return newElement;
}

inline void * dsListErase(ds_list * const list, void * const pos) {
    element * const prev = ((element *) pos)->prev;
    element * const next = ((element *) pos)->next;
    free(pos);
    if(prev)
        prev->next = next;
    else
        list->front = next;
    next->prev = prev;
    list->size--;
    return next;
}

inline void * dsListPushFront(ds_list * const list) {
    element * const newElement = malloc(sizeof(element) + list->typeSize);
    *newElement = (element) { .next = list->front, .prev = 0 };
    list->front->prev = newElement;
    list->front = newElement;
    list->size++;
    return newElement;
}

inline void dsListPopFront(ds_list * const list) {
    element * const first = list->front->next;
    free(list->front);
    list->front = first;
    first->prev = 0;
    list->size--;
}

inline void * dsListPushBack(ds_list * const list) {
    return dsListInsert(list, list->end);
}

inline void dsListPopBack(ds_list * const list) {
    dsListErase(list, list->end->prev);
}

void dsListReverse(ds_list * const list) {
    if(!list->size)
        return;
    list->end->next = list->end->prev;
    list->end->prev = list->end->prev->next = 0;
    element * temp;
    for(element * iter = list->end; iter; iter = iter->prev) {
        temp = iter->prev;
        iter->prev = iter->next;
        iter->next = temp;
    }
    list->front = temp->prev;
}
