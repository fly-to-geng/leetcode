#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *g_nums = NULL;

typedef struct AA{
    struct AA *left;
    struct AA *right;
    int begin, end;
    int val;
} NumArray;

NumArray* create(int *nums, int begin, int end) {
    g_nums = nums;
    if (begin > end) return NULL;
    if (begin == end) {
        NumArray *newNode = (NumArray*)malloc(sizeof(NumArray));
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->begin = begin;
        newNode->end = end;
        newNode->val = nums[begin];
        return newNode;
    }
    int mid = (begin + end) / 2;
    NumArray* newNode = (NumArray*)malloc(sizeof(NumArray));
    newNode->begin = begin;
    newNode->end = end;
    newNode->left = create(nums, begin, mid);
    newNode->right = create(nums, mid + 1, end);
    newNode->val = newNode->left->val + newNode->right->val;
    return newNode;
}
NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray* root = create(nums, 0, numsSize - 1);
    return root;
}

void numArrayAdd(NumArray* obj, int i, int added) {
    if (obj == NULL) return;
    if (obj->begin == obj->end && obj->begin == i) {
        obj->val += added;
        return;
    }
    obj->val += added;
    int mid = (obj->begin + obj->end) / 2;
    if (i <= mid) {
        numArrayAdd(obj->left, i, added);
    } else {
        numArrayAdd(obj->right, i, added);
    }
}
void numArrayUpdate(NumArray* obj, int i, int val) {
    int added = val - g_nums[i];
    numArrayAdd(obj, i, added);
    g_nums[i] = val;
}

int numArraySumRange(NumArray* obj, int i, int j) {
    if (i <= obj->begin && j >= obj->end) {
        return obj->val;
    }
    if (i > obj->end || j < obj->begin) {
        return 0;
    }
    int left = numArraySumRange(obj->left, i, j);
    int right = numArraySumRange(obj->right, i, j);
    return left + right;
}

void numArrayFree(NumArray* obj) {
    g_nums = NULL;
    if (obj == NULL) return;
    if (obj->left == NULL && obj->right == NULL) {
        free(obj);
        obj = NULL;
        return;
    }
    free(obj->left);
    free(obj->right);
    obj->left = NULL;
    obj->right = NULL;
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
