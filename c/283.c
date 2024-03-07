void moveZeroes(int* nums, int numsSize){
    int i, j;
    int count = 0; // 0 的个数
    for (i = numsSize - 1; i >= 0; i--) {
        // 一旦遇到0, 就把后面的移动到前面，最后补0, count+1
        if (nums[i] == 0) {
            for (j = i + 1; j < numsSize - count; j++) {
                nums[j - 1] = nums[j];
            }
            nums[j - 1] = 0;
            count += 1;
        }
    }
}