/*
 * 使用堆排序
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * 使用数组表示的左孩子是堆，位置0存放第一个元素
 * 节点 i  2 * i + 1
 * 节点 i 的右孩子是 2 * i + 2
 * 节点 i 的父亲是 (i - 1) / 2
 */
int left(int i)
{
    return (i << 1) + 1;
}
int right(int i)
{
    return (i << 1) + 2;
}
int parent(int i)
{
    if (i <= 0) {
        return -1;
    }
    return (i - 1) >> 1;
}
void swap(int *array, int index1, int index2)
{
    int tmp;
    tmp = array[index1];
    array[index1] = array[index2];
    array[index2] = tmp;
}
// 向下调整节点 i, 大顶堆
void adjustDown(int *heap, int heapSize, int i)
{
    int leftNode, rightNode;
    int largest = i;
    leftNode = left(i);
    if (leftNode < heapSize && heap[leftNode] > heap[largest]) {
        largest = leftNode;
    }
    rightNode = right(i);
    if (rightNode < heapSize && heap[rightNode] > heap[largest]) {
        largest = rightNode;
    }
    if (largest == i) {
        return;
    }
    swap(heap, i, largest);
    adjustDown(heap, heapSize, largest);
}
// 向上调整节点 i， 大顶堆
void adjustUp(int *heap, int heapSize, int i)
{
    int parentNode;
    parentNode = parent(i);
    if (i != -1 && heap[parentNode] < heap[i]) {
        swap(heap, i, parentNode);
        adjustUp(heap, heapSize, parentNode);
    }
    return;
}
// 建立堆
int* buildHeap(int *array, int arraySize, int *heapSize)
{
    int *heap;
    int n = arraySize / 2 - 1;
    int i;

    heap = (int*)malloc(sizeof(int) * arraySize);
    memset(heap, 0, sizeof(int) * arraySize);
    memcpy(heap, array, sizeof(int) * arraySize);

    *heapSize = arraySize;
    for (i = n; i >= 0; i--) {
        adjustDown(heap, arraySize, i);
    }

    return heap;
}
int findKthLargest(int* nums, int numsSize, int k){
    int *heap;
    int heapSize;
    int ans, i;
    int tmpK = k - 1;
    heap = buildHeap(nums, numsSize, &heapSize);
    while (tmpK--) {
        swap(heap, 0, heapSize-1);
        heapSize--;
        adjustDown(heap, heapSize, 0);
    }

    ans = heap[0];

    free(heap);
    return ans;
}

/*
 * 使用归并排序
 */
#include <stdio.h>
#include <stdlib.h>

void merge(int *array, int start, int mid, int end)
{
    int lstart = start;
    int lend = mid;
    int rstart = mid + 1;
    int rend = end;
    int *tmp;
    int tmpEnd = 0;
    int index, i;

    tmp = (int*)malloc(sizeof(int) * (end - start + 1));
    while (tmpEnd < (end-start+1)) {
        if (lstart <= lend && rstart <= rend && array[lstart] < array[rstart]) {
            tmp[tmpEnd++] = array[lstart++];
        } else if (lstart <= lend && rstart <= rend && array[lstart] > array[rstart]) {
            tmp[tmpEnd++] = array[rstart++];
        } else if (lstart > lend) {
            tmp[tmpEnd++] = array[rstart++];
        } else {
            tmp[tmpEnd++] = array[lstart++];
        }
    }
    index = start;
    for (i = 0; i < tmpEnd; i++) {
        array[index++] = tmp[i];
    }
    return;
}
void mergeSort(int *array, int start, int end)
{
    int mid;
    if (end <= start) {
        return;
    }
    mid = (end + start) / 2;
    mergeSort(array,start, mid);
    mergeSort(array, mid + 1, end);
    merge(array, start, mid, end);
    return;
}
int findKthLargest(int* nums, int numsSize, int k){
    return 0;
}

/*
 * 使用快速排序
 */
#include <stdio.h>
#include <stdlib.h>

void swap(int *array, int index1, int index2)
{
    int tmp = array[index1];
    array[index1] = array[index2];
    array[index2] = tmp;
}
int partition(int *array, int start, int end)
{
    int x = end;
    int i = start;
    int j;
    for (j = start; j < end; j++) {
        if (array[j] < array[end]) {
            swap(array, i, j);
            i++;
        }
    }
    swap(array, i, end);
    return i;
}
void quickSort(int *array, int start, int end)
{
    int mid;
    if (start >= end) {
        return;
    }
    mid = partition(array, start, end);
    quickSort(array, start, mid - 1);
    quickSort(array, mid + 1, end);
}
int findKthLargest(int* nums, int numsSize, int k){
    int mid;
    int start = 0;
    int end = numsSize - 1;
    while (start <= end) {
        mid = partition(nums, start, end);
        if (mid == numsSize - k) {
            return nums[mid];
        } else if (mid < numsSize - k) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return 0;
}