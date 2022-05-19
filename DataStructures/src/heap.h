#pragma once
#ifndef _DS_HEAP_H_
#define _DS_HEAP_H_

#include <stddef.h>
#include "range.h"
#include "array.h"

typedef _Bool (* CMP)(void const *, void const *);

typedef struct {
    size_t typeSize;
    ds_range range;
    CMP cmp;
} ds_heap;

void dsHeapMake(ds_heap const * heap);
void dsHeapPush(ds_heap const * heap);
void dsHeapPop(ds_heap const * heap);
void dsHeapSort(ds_heap const * heap);

#endif // _DS_HEAP_H_
