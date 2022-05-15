#include <stdlib.h>
#include <string.h>
#include "array.h"

struct ds_array {
    size_t const valueSize;
    size_t size, capacity;
    unsigned char * data;
};

static inline ds_array dsArrayInit(size_t const valueSize, size_t const size, size_t const capacity) {
    ds_array arr = { .valueSize = valueSize, .size = size, .capacity = capacity };
    arr.data = malloc(capacity * valueSize);
    return arr;
}

inline ds_array dsArrayCreate(size_t const cap, size_t const valueSize) {
    return dsArrayInit(valueSize, 0, cap);
}

ds_array dsArrayCreateVal(size_t const count, size_t const valueSize, void const * restrict const value) {
    ds_array arr = dsArrayInit(valueSize, count, count);
    for(size_t i = 0; i < count; i++)
        memcpy(arr.data + i * valueSize, value, valueSize);
    return arr;
}

ds_array dsArrayCreateAlloc(size_t const count, size_t const valueSize, void (*alloc)(void *)) {
    ds_array arr = dsArrayInit(valueSize, count, count);
    for(size_t i = 0; i < count; i++)
        alloc(arr.data + i * valueSize);
    return arr;
}

inline ds_array dsArrayCreateCopy(ds_array const * const src) {
    ds_array arr = dsArrayInit(src->valueSize, src->size, src->size);
    memcpy(arr.data, src->data, arr.size * arr.valueSize);
    return arr;
}

ds_array dsArrayCreateFrom(ds_array const * const src, size_t const valueSize, void (*alloc)(void *, void const *)) {
    ds_array arr = dsArrayInit(valueSize, src->size, src->size);
    for(size_t i = 0; i < arr.size; i++)
        alloc(arr.data + i * valueSize, src->data + i * src->valueSize);
    return arr;
}

inline void dsArrayDelete(ds_array * const arr) {
    free(arr->data);
    arr->size = arr->capacity = 0;
    arr->data = 0;
}

inline void dsArrayDeleteDealloc(ds_array * const arr, void (*dealloc)(void *)) {
    dsArrayClearOp(arr, dealloc);
    dsArrayDelete(arr);
}

inline void * dsArrayAt(ds_array const * const arr, size_t const pos) {
    return pos < arr->size ? arr->data + pos * arr->valueSize : 0;
}

inline void * dsArrayFront(ds_array const * const arr) {
    return arr->data;
}

inline void * dsArrayBack(ds_array const * const arr) {
    return arr->data + arr->size * arr->valueSize;
}

inline size_t dsArraySize(ds_array const * const arr) {
    return arr->size;
}

inline size_t dsArrayCapacity(ds_array const * const arr) {
    return arr->capacity;
}

inline void dsArrayResize(ds_array * const arr, size_t const cap) {
    arr->data = realloc(arr->data, cap * arr->valueSize);
    arr->capacity = cap;
    if(cap < arr->size)
        arr->size = cap;
}

inline void dsArrayClear(ds_array * const arr) {
    arr->size = 0;
}

void dsArrayClearOp(ds_array * const arr, void (*dealloc)(void *)) {
    for(size_t i = 0; i < arr->size; i++)
        dealloc(arr->data + i * arr->valueSize);
    dsArrayClear(arr);
}

void * dsArrayInsert(ds_array * const arr, size_t const pos, size_t const count) {
    if(pos > arr->size)
        return 0;
    size_t const    firstSize = pos * arr->valueSize,
                    secondOffset = (pos + count) * arr->valueSize,
                    secondSize = (arr->size - pos) * arr->valueSize;
    unsigned char * const secondSrc = arr->data + firstSize;
    arr->size += count;
    if(arr->size <= arr->capacity) {
        memmove(arr->data + secondOffset, secondSrc, secondSize);
        return secondSrc;
    }
    unsigned char * buffer = malloc((arr->capacity = arr->size << 1) * arr->valueSize);
    memcpy(buffer, arr->data, firstSize);
    memcpy(buffer + secondOffset, secondSrc, secondSize);
    free(arr->data);
    return (arr->data = buffer) + firstSize;
}

inline void * dsPushBack(ds_array * const arr, size_t const count) {
    size_t const offset = arr->size * arr->valueSize;
    arr->size += count;
    if(arr->size > arr->capacity)
        arr->data = realloc(arr->data, (arr->capacity = arr->size <<  1) * arr->valueSize);
    return arr->data + offset;
}
