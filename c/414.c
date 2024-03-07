int thirdMax(int* nums, int numsSize){
    long long max1 = LLONG_MIN;
    long long max2 = LLONG_MIN;
    long long max3 = LLONG_MIN;
    int i;

    for (i = 0; i < numsSize; i++) {
        if (nums[i] > max1) {
            max3 = max2;
            max2 = max1;
            max1 = nums[i];
        }
        if (nums[i] < max1 && nums[i] > max2) {
            max3 = max2;
            max2 = nums[i];
        }
        if (nums[i] < max2 && nums[i] > max3) {
            max3 = nums[i];
        }
    }
    if (max3 == LLONG_MIN) { return max1; }
    return max3;
}