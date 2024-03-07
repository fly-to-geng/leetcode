#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maxSubArray(int* nums, int numsSize){
    int ans = 0;
    int i;
    int pre;

    if (nums == NULL || numsSize == 0) {
        return ans;
    }

    ans = nums[0];
    pre = nums[0];
    for (i = 1; i < numsSize; i++) {
        if (pre + nums[i] > nums[i]) {
            pre = pre + nums[i];
            ans = MAX(ans, pre);
        } else {
            pre = nums[i];
            ans = MAX(ans, pre);
        }
    }
    return ans;
}