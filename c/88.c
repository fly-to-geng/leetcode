* 从 start 开始查找插入位置并返回下一个位置 */
int insert(int *nums, int size, int start, int value)
{
    int i = start;
    while (i < size && nums[i] < value) i++;
    if (i >= size) {
        nums[i] = value;
        return i;
    }
    for (int j = size - 1; j >= i; j--) {
        nums[j + 1] = nums[j];
    }
    nums[i] = value;
    return i;
}
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    if (nums1 == NULL || nums1Size <= 0 || nums2 == NULL || nums2Size <= 0) {
        return;
    }

    int i;
    int start = 0;
    for (i = 0; i < n; i++) {
        start = insert(nums1, m + i, start, nums2[i]);
    }
    return;
}