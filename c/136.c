int singleNumber(int* nums, int numsSize){
    int ans = 0;
    int i;

    if (nums == NULL || numsSize == 0) {
        return -1;
    }

    ans = nums[0];
    for (i = 1; i < numsSize; i++) {
        ans ^= nums[i];
    }

    return ans;
}