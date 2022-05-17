#pragma once
#ifndef _DS_LIST_H_
#define _DS_LIST_H_

#include <stddef.h>

typedef struct ds_list ds_list;

ds_list * dsList(size_t typeSize);
ds_list * dsListCopy(ds_list const * src);
void dsListDelete(ds_list * list);

void * dsListAt(ds_list const * list, size_t pos);
void * dsListData(void const * pos);
void * dsListNext(void const * pos);
void * dsListPrev(void const * pos);
void * dsListFront(ds_list const * list);
void * dsListBack(ds_list const * list);
void * dsListEnd(ds_list const * list);

size_t dsListSize(ds_list const * list);

void dsListClear(ds_list * list);
void * dsListInsert(ds_list * list, void * pos);
void * dsListErase(ds_list * list, void * pos);
void * dsListPushFront(ds_list * list);
void dsListPopFront(ds_list * list);
void * dsListPushBack(ds_list * list);
void dsListPopBack(ds_list * list);

void dsListReverse(ds_list * list);

#define dsIterList(it, list) \
    for(void * it = dsListFront(list); it != dsListEnd(list); it = dsListNext(it))

#endif // _DS_LIST_H_
