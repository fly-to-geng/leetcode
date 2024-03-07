#include <stdio.h>
#include <uthash.h>

int partition(int *arr, int start, int end)
{
    int i = start - 1;
    int tmp;
    for (int j = start; j < end; j++) {
        if (arr[j] <= arr[end]) {
            i = i + 1;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    tmp = arr[i+1];
    arr[i+1] = arr[end];
    arr[end] = tmp;
    return i + 1;
}

void quickSort(int *arr, int start, int end)
{
    if (start >= end) return;
    int mid = partition(arr, start, end);
    quickSort(arr, start, mid - 1);
    quickSort(arr, mid + 1, end);
    return;
}

void sort(const void *arr, int n)
{
    
}

int main()
{
    int a[] = {7,2,1,3,9,1,0};
    int n = sizeof(a) / sizeof(a[0]);
    quickSort(a, 0, n - 1);
    return 0;   
}