#include <stdlib.h>
#include <string.h>
#include "array.h"

struct ds_array {
    size_t typeSize, size, capacity;
    unsigned char * data;
};

static inline ds_array * dsArrayInit(size_t const typeSize, size_t const size, size_t const capacity) {
    ds_array * const arr = malloc(sizeof(ds_array));
    *arr = (ds_array) { .typeSize = typeSize, .size = size, .capacity = capacity, .data = malloc(capacity * typeSize) };
    return arr;
}

static inline void * dsArrayPos(ds_array const * const arr, size_t const pos) {
    return arr->data + pos * arr->typeSize;
}

inline ds_array * dsArray(size_t const typeSize, size_t const cap) {
    return dsArrayInit(typeSize, cap, cap);
}

inline ds_array * dsArrayCopy(ds_array const * const src) {
    ds_array * const arr = dsArrayInit(src->typeSize, src->size, src->size);
    memcpy(arr->data, src->data, arr->size * arr->typeSize);
    return arr;
}

inline void dsArrayDelete(ds_array * const arr) {
    free(arr->data);
    free(arr);
}

inline void * dsArrayAt(ds_array const * const arr, size_t const pos) {
    return pos < arr->size ? dsArrayPos(arr, pos) : 0;
}

inline void * dsArrayData(ds_array const * const arr) {
    return arr->data;
}

inline void * dsArrayBack(ds_array const * const arr) {
    return dsArrayPos(arr, arr->size - 1);
}

inline void * dsArrayEnd(ds_array const * const arr) {
    return dsArrayPos(arr, arr->size);
}

inline size_t dsArraySize(ds_array const * const arr) {
    return arr->size;
}

inline size_t dsArrayCapacity(ds_array const * const arr) {
    return arr->capacity;
}

inline void dsArrayResize(ds_array * const arr, size_t const cap) {
    arr->data = realloc(arr->data, (arr->capacity = cap) * arr->typeSize);
    if(arr->size > cap)
        arr->size = cap;
}

inline void dsArrayClear(ds_array * const arr) {
    arr->size = 0;
}

inline void * dsArrayInsert(ds_array * const arr, size_t const pos) {
    return dsArrayInsertRange(arr, pos, 1).begin;
}

inline void dsArrayErase(ds_array * const arr, size_t const pos) {
    dsArrayEraseRange(arr, pos, 1);
}

inline void * dsArrayPushBack(ds_array * const arr) {
    if(arr->size == arr->capacity)
        arr->data = realloc(arr->data, (arr->capacity <<= 1) * arr->typeSize);
    return dsArrayPos(arr, arr->size++);
}

inline void dsArrayPopBack(ds_array * const arr) {
    arr->size--;
}

inline ds_range dsArrayRange(ds_array const * const arr) {
    return (ds_range) { .begin = dsArrayData(arr), .end = dsArrayEnd(arr) };
}

inline ds_range dsArraySlice(ds_array const * const arr, size_t const pos, size_t const count) {
    return (ds_range) { .begin = dsArrayPos(arr, pos), .end = dsArrayPos(arr, pos + count) };
}

ds_range dsArrayInsertRange(ds_array * const arr, size_t const pos, size_t const count) {
    if(pos > arr->size)
        return (ds_range) { .begin = 0, .end = 0 };
    arr->size += count;
    size_t const secondSize = (arr->size - pos) * arr->typeSize;
    void * const secondSrc = dsArrayPos(arr, pos);
    if(arr->size > arr->capacity) {
        unsigned char * const buffer = malloc((arr->capacity = arr->size << 1) * arr->typeSize);
        memcpy(buffer, arr->data, pos * arr->typeSize);
        memcpy(buffer + (pos + count) * arr->typeSize, secondSrc, (arr->size - pos) * arr->typeSize);
        free(arr->data);
        arr->data = buffer;
    } else
        memmove(dsArrayPos(arr, pos + count), secondSrc, secondSize);
    return dsArraySlice(arr, pos, count);
}

inline void dsArrayEraseRange(ds_array * const arr, size_t const pos, size_t const count) {
    memmove(dsArrayPos(arr, pos), dsArrayPos(arr, pos + count), (arr->size - pos - count) * arr->typeSize);
    arr->size -= count;
}
