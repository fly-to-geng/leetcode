#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *arr;
    int *nums;
    int size;    
} NumArray;

void add(NumArray *obj, int i, int val) {
    i = i + 1;
    while (i <= obj->size) {
        obj->arr[i - 1] += val;
        i += (i & -i);
    }
}

NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray *array = (NumArray*)malloc(sizeof(NumArray));
    array->arr = (int*)malloc(sizeof(int) * numsSize);
    array->size = numsSize;
    array->nums = nums;
    for (int i = 0; i < numsSize; i++) {
        array->arr[i] = 0;
    }
    for (int i = 0; i < numsSize; i++) {
        add(array, i, nums[i]);
    }
    return array;
}


int query(NumArray *obj, int i) {
    int sum = 0;
    i = i + 1;
    while (i > 0) {
        sum += obj->arr[i - 1];
        i -= (i & -i);
    }
    return sum;
}
void numArrayUpdate(NumArray* obj, int i, int val) {
    int added = val - obj->nums[i];
    add(obj, i, added);
    obj->nums[i] = val;
}

int numArraySumRange(NumArray* obj, int i, int j) {
    int ans = query(obj, j) - query(obj, i - 1);
    return ans;
}

void numArrayFree(NumArray* obj) {
    free(obj->arr);
    free(obj);
}

int main()
{
    int nums[3] = {1, 3, 5};
    int numsSize = 3;
    NumArray* obj = numArrayCreate(nums, numsSize);
    
    int param_2 = numArraySumRange(obj, 0, 2);
    int expected_2 = 9;

    numArrayUpdate(obj, 1, 2);

    int param_3 = numArraySumRange(obj, 0, 2);
    int expected_3 = 8;
    
    numArrayFree(obj);
    return 0;
}
