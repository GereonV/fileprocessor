#include <stdio.h>
#include "array.h"

int main() {
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
    dsIterArray(int, ptr, arr)
        printf("%d\n", *ptr);
}
