int search(int* nums, int numsSize, int target){
    int i, j, mid;
    i = 0;
    j = numsSize - 1;
    while (i <= j) {
        mid = (i + j) / 2;
        if (target == nums[mid]) {
            return mid;
        } else if (target > nums[mid]) {
            if (nums[mid] <= nums[j] && nums[j] < target) {
                j = mid - 1;
            } else {
                i = mid + 1;
            }
        } else if (target < nums[mid]){
            if (nums[i] <= nums[mid] && nums[i] > target) {
                i = mid + 1;
            } else {
                j = mid - 1;
            }
        }
    }
    return -1;
}