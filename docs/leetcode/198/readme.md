# [198. 打家劫舍](https://leetcode-cn.com/problems/house-robber/)

## 题目描述

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

 

示例 1：

    输入：[1,2,3,1]
    输出：4
    解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
         偷窃到的最高金额 = 1 + 3 = 4 。


示例 2：

    输入：[2,7,9,3,1]
    输出：12
    解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
         偷窃到的最高金额 = 2 + 9 + 1 = 12 。
 

提示：

    0 <= nums.length <= 100
    0 <= nums[i] <= 400

## 解题思路

深度优先搜索，遍历所有的情况，可以通过大部分用例，但是最后会超时。

```c
#define MAX(a,b) ((a) > (b)) ? (a) : (b)
int maxv = 0;

void dfs(int *nums, int numsSize, int i, int tmpMax)
{
    if (i >= numsSize) {
        maxv = MAX(maxv, tmpMax);
        return;
    }

    // 选择i
    dfs(nums, numsSize, i + 2, tmpMax + nums[i]);
    
    // 不选择i
    dfs(nums, numsSize, i + 1, tmpMax);
}
int rob(int* nums, int numsSize){
    int ans = 0;
    maxv = 0;
    if (numsSize <= 0) {
        return maxv;
    }
    dfs(nums, numsSize, 0, ans);
    return maxv;
}
```

递归消耗时间太多，只适合N较小的情况，下面使用动态规划，计算以每个数字结尾的情况下偷的最多的钱，然后取最大值。

```c
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


```
