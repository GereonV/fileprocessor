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
}

static void list() {
    ds_list * list = dsList(sizeof(int));
    *(int *) dsListAt(dsListPushFront(list)) = 69;
    *(int *) dsListAt(dsListPushFront(list)) = 42;
    *(int *) dsListAt(dsListPushBack(list)) = 42;
    *(int *) dsListAt(dsListInsert(list, dsListNext(dsListNext(dsListFront(list))))) = 420;
    dsListPopFront(list);
    dsListPopBack(list);
    *(int *) dsListAt(dsListInsert(list, dsListNext(dsListFront(list)))) = 42;
    dsListErase(list, dsListNext(dsListFront(list)));
    dsListClear(list);
    *(int *) dsListAt(dsListPushBack(list)) = 36;
    *(int *) dsListAt(dsListPushBack(list)) = 72;
    ds_list * list2 = dsListCopy(list);
    dsListDelete(list);
    list = list2;
    dsListReverse(list);
    dsIterList(ptr, list)
        printf("%d\n", *(int *) dsListAt(ptr));
}

int main() {
    list();
}
