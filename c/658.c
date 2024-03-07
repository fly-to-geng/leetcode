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