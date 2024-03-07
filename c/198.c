#define MAX(a,b) ((a) > (b)) ? (a) : (b)
int rob(int* nums, int numsSize){
    int *dp;
    int maxv = 0;
    int premax = 0;
    int i;

    if (numsSize <= 0) {
        return 0;
    }
    if (numsSize == 1) {
        return nums[0];
    }
    if (numsSize == 2) {
        return MAX(nums[0],nums[1]);
    }
    dp = (int*)malloc(sizeof(int) * numsSize);
    dp[0] = nums[0];
    dp[1] = nums[1];
    premax = nums[0];
    maxv = MAX(nums[0], nums[1]);

    for (i = 2; i < numsSize; i++) {
        dp[i] = premax + nums[i];
        premax = MAX(premax, dp[i-1]);
        maxv = MAX(maxv, dp[i]);
    }
    return maxv;
}