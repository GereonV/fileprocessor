#include <stdlib.h>
#include <string.h>
#include "heap.h"

static inline size_t dsHeapSize(ds_heap const * const heap) {
    return ((unsigned char *) heap->range.end - (unsigned char *) heap->range.begin) / heap->typeSize;
}

static inline void * dsHeapPos(ds_heap const * const heap, size_t const pos) {
    return (unsigned char *) heap->range.begin + pos * heap->typeSize;
}

static inline void swap(size_t const typeSize, void * const a, void * const b, void * const buffer) {
    memcpy(buffer, a, typeSize);
    memcpy(a, b, typeSize);
    memcpy(b, buffer, typeSize);
}

static void heapifyUp(ds_heap const * const heap, size_t pos, void * const buffer) {
    void * p, * ptr = dsHeapPos(heap, pos);
    while(pos) {
        size_t const parent = (pos - 1) >> 1;
        p = dsHeapPos(heap, parent);
        if(heap->cmp(ptr, p))
            return;
        swap(heap->typeSize, p, ptr, buffer);
        pos = parent;
        ptr = p;
    }
}

static void heapifyDown(ds_heap const * const heap, size_t const size, size_t pos, void * const buffer) {
    void * p = dsHeapPos(heap, pos);
    for(;;) {
        size_t const left = (pos << 1) + 1, right = left + 1;
        void * const l = dsHeapPos(heap, left), * const r = dsHeapPos(heap, right);
        size_t largest = pos;
        void * ptr = p;
        if(left >= size)
            return;
        if(heap->cmp(p, l)) {
            largest = left;
            ptr = l;
        }
        if(right < size && heap->cmp(ptr, r)) {
            largest = right;
            ptr = r;
        } else if(largest == pos) {
            return;
        }
        swap(heap->typeSize, p, ptr, buffer);
        pos = largest;
        p = ptr;
    }
}

void dsHeapMake(ds_heap const * const heap) {
    size_t const size = dsHeapSize(heap);
    if(!size)
        return;
    void * const buffer = malloc(heap->typeSize);
    for(size_t i = size >> 1; i--;)
        heapifyDown(heap, size, i, buffer);
    free(buffer);
}

inline void dsHeapPush(ds_heap const * const heap) {
    size_t const size = dsHeapSize(heap);
    if(!size)
        return;
    void * const buffer = malloc(heap->typeSize);
    heapifyUp(heap, size - 1, buffer);
    free(buffer);
}

inline void dsHeapPop(ds_heap const * const heap) {
    size_t const size = dsHeapSize(heap);
    if(!size)
        return;
    void * const buffer = malloc(heap->typeSize);
    swap(heap->typeSize, heap->range.begin, dsHeapPos(heap, size - 1), buffer);
    heapifyDown(heap, size - 1, 0, buffer);
    free(buffer);
}

void dsHeapSort(ds_heap const * const heap) {
    for(ds_heap h = *heap; h.range.begin != h.range.end; h.range.end = (unsigned char *) h.range.end - h.typeSize)
        dsHeapPop(&h);
}
