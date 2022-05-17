#include <stdio.h>
#include "array.h"
#include "list.h"

static void array() {
    ds_array * arr = dsArray(sizeof(int), 4);
    ds_range range = dsArrayRange(arr);
    dsIterRange(int, ptr, range)
        *ptr = 42;
    *(int *) dsArrayAt(arr, 1) = 69;
    *(int *) dsArrayInsert(arr, 3) = 420;
    *(int *) dsArrayPushBack(arr) = 36;
    ds_array * arr2 = dsArrayCopy(arr);
    dsArrayDelete(arr);
    arr = arr2;
    range = dsArrayInsertRange(arr, 0, 4);
    dsIterRange(int, ptr, range)
        *ptr = -1;
    dsArrayEraseRange(arr, 4, 6);
    dsArrayPopBack(arr);
    dsArrayResize(arr, 1);
    dsArrayResize(arr, 10);
    dsArrayClear(arr);
    range = dsArrayRange(arr);
    dsIterRange(int, ptr, range)
        printf("%d\n", *ptr);
    dsArrayDelete(arr);
}

static void list() {
    ds_list * list = dsList(sizeof(int));
    *(int *) dsListData(dsListPushFront(list)) = 69;
    *(int *) dsListData(dsListPushFront(list)) = 42;
    *(int *) dsListData(dsListPushBack(list)) = 42;
    *(int *) dsListData(dsListInsert(list, dsListAt(list, 3))) = 420;
    dsListPopFront(list);
    dsListPopBack(list);
    *(int *) dsListData(dsListInsert(list, dsListNext(dsListFront(list)))) = 42;
    dsListErase(list, dsListNext(dsListFront(list)));
    dsListClear(list);
    *(int *) dsListData(dsListPushBack(list)) = 36;
    *(int *) dsListData(dsListPushBack(list)) = 72;
    ds_list * list2 = dsListCopy(list);
    dsIterList(ptr, list)
        printf("%d\n", *(int *) dsListData(ptr));
    dsListReverse(list2);
    dsIterListR(ptr, list2)
        printf("%d\n", *(int *) dsListData(ptr));
    dsListDelete(list);
    dsListDelete(list2);
}

int main() {
    array();
    list();
}
