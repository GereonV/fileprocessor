#pragma once
#ifndef _DS_ARRAY_H_
#define _DS_ARRAY_H_

#include <stddef.h>
#include "range.h"

typedef struct ds_array ds_array;

ds_array * dsArray(size_t typeSize, size_t size);
ds_array * dsArrayCopy(ds_array const * src);
ds_array * dsArrayCopyRange(size_t typeSize, ds_range const * range);
void dsArrayDelete(ds_array * arr);

void * dsArrayAt(ds_array const * arr, size_t pos);
void * dsArrayData(ds_array const * arr);
void * dsArrayBack(ds_array const * arr);
void * dsArrayEnd(ds_array const * arr);

size_t dsArraySize(ds_array const * arr);
size_t dsArrayCapacity(ds_array const * arr);
void dsArrayResize(ds_array * arr, size_t cap);

void dsArrayClear(ds_array * arr);
void * dsArrayInsert(ds_array * arr, size_t pos);
void dsArrayErase(ds_array * arr, size_t pos);
void * dsArrayPushBack(ds_array * arr);
void dsArrayPopBack(ds_array * arr);

ds_range dsArrayRange(ds_array const * arr);
ds_range dsArraySlice(ds_array const * arr, size_t pos, size_t count);
ds_range dsArrayInsertRange(ds_array * arr, size_t pos, size_t count);
void dsArrayEraseRange(ds_array * arr, size_t pos, size_t count);

#endif // _DS_ARRAY_H_
