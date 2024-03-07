# [658. 找到 K 个最接近的元素](https://leetcode-cn.com/problems/find-k-closest-elements/)

## 题目描述

给定一个排序好的数组，两个整数 k 和 x，从数组中找到最靠近 x（两数之差最小）的 k 个数。返回的结果必须要是按升序排好的。如果有两个数与 x 的差值一样，优先选择数值较小的那个数。

示例 1:

      输入: [1,2,3,4,5], k=4, x=3
      输出: [1,2,3,4]
 

示例 2:

      输入: [1,2,3,4,5], k=4, x=-1
      输出: [1,2,3,4]
 

说明:

      k 的值为正数，且总是小于给定排序数组的长度。
      数组不为空，且长度不超过 104
      数组里的每个元素与 x 的绝对值不超过 104

## 解题思路

1. 使用二分查找找到 x 应该插入的位置
2. 使用双指针搜索附近元素，找到距离最近的K个
3. 排序输出

```c
#define ABS(a) ((a) >= 0 ? (a) : (-(a)))
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void swap(int *arr, int index1, int index2)
{
    int tmp;

    if (index1 == index2) {
        return;
    }

    tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
    return;
}

int partition(int *arr, int start, int end)
{
    int x, i, j;

    x = arr[end];
    j = start - 1;
    for (i = start; i < end; i++) {
        if (arr[i] <= x) {
            j = j + 1;
            swap(arr, j, i);
        }
    }
    swap(arr, j + 1, end);
    return j + 1;
}
void sorted(int *arr, int start, int end)
{
    int mid;

    if (start >= end) {
        return;
    }

    mid = partition(arr, start, end);
    sorted(arr, start, mid - 1);
    sorted(arr, mid + 1, end);
    return;
}
int BinaryFind(int *arr, int arrSize, int target)
{
    int left = 0;
    int right = arrSize - 1;
    int mid;

    while (left < right) {
        mid = (left + right) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize){
    int *ans;
    int ansEnd = 0;
    int left, right, pos;

    if (arr == NULL || arrSize == 0) {
        return NULL;
    }

    // 二分查找找到 x 应该插入 arr 的位置
    pos = BinaryFind(arr, arrSize, x);

    // 从 pos 开始双指针左右搜索， 找与 x 差值最小的添加到结果中
    ans = (int*)malloc(sizeof(int) * k);
    left = pos - 1;
    right = pos;
    while (ansEnd < k) {
        if (left >= 0 && right < arrSize) {
            if (ABS(arr[left] - x) <= ABS(arr[right] - x)) {
                ans[ansEnd++] = arr[left];
                left -= 1;
            } else {
                ans[ansEnd++] = arr[right];
                right += 1;
            }
        } else if (left >= 0) {
            ans[ansEnd++] = arr[left];
            left -= 1;
        } else {
            ans[ansEnd++] = arr[right];
            right += 1;
        }
    }

    sorted(ans, 0, ansEnd - 1);

    *returnSize = ansEnd;
    return ans;
}
```
