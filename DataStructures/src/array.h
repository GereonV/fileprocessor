#pragma once
#ifndef _DS_ARRAY_H_
#define _DS_ARRAY_H_

#include <stddef.h>

typedef struct ds_array ds_array;

ds_array dsArrayCreate(size_t cap, size_t valueSize);
ds_array dsArrayCreateVal(size_t count, size_t valueSize, void const * value);
ds_array dsArrayCreateAlloc(size_t count, size_t valueSize, void (*alloc)(void *));

ds_array dsArrayCreateCopy(ds_array const * src);
ds_array dsArrayCreateFrom(ds_array const * src, size_t valueSize, void (*alloc)(void *, void const *));

void dsArrayDelete(ds_array * arr);
void dsArrayDeleteDealloc(ds_array * arr, void (*dealloc)(void *));

void * dsArrayAt(ds_array const * arr, size_t pos);
void * dsArrayFront(ds_array const * arr);
void * dsArrayBack(ds_array const * arr);

size_t dsArraySize(ds_array const * arr);
size_t dsArrayCapacity(ds_array const * arr);
void dsArrayResize(ds_array * arr, size_t cap);

void dsArrayClear(ds_array * arr);
void dsArrayClearOp(ds_array * arr, void (*dealloc)(void *));
void * dsArrayInsert(ds_array * arr, size_t pos, size_t count);
void * dsPushBack(ds_array * arr, size_t count);

#endif // _DS_ARRAY_H_
