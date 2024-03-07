# [739. 每日温度](https://leetcode-cn.com/problems/daily-temperatures/)

## 题目描述

请根据每日 气温 列表，重新生成一个列表。对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用 0 来代替。

例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。

提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。

## 解题思路

暴力方法，两层循环，最后两个用例无法通过。
35 / 37 个通过测试用例

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* T, int TSize, int* returnSize){
    int *ans;
    int i, j;

    ans = (int*)malloc(sizeof(int) * TSize);
    memset(ans, 0, sizeof(int) * TSize);
    for (i = 0; i < TSize - 1; i++) {
        for (j = i + 1; j < TSize; j++) {
            if (T[j] > T[i]) {
                ans[i] = j - i;
                break;
            }
        }
    }
    *returnSize = TSize;
    return ans;
}
```

暴力方法每次都到扫描到最后，无法利用前一次扫描的信息，所以时间复杂度很高。
我们采取从后道前的方法扫描每一个数字，
当 nums[i] < nums[i+1] 时， ans[i] = 1
当nums[i] >= nums[i+1] 时， 需要向后找到第一个大于nums[i]的数字
在向后找的时候，因为已经知道了任意一个数字第一个大于它的数字出现的位置，所以可以不必每次移动一个位置，而是跳跃着找，这样明显可以快很多。

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* T, int TSize, int* returnSize){
    int *ans;
    int i, j;

    ans = (int*)malloc(sizeof(int) * TSize);
    memset(ans, 0, sizeof(int) * TSize);
    for (i = TSize - 2; i >= 0; i--) {
        if (T[i] < T[i + 1]) {
            ans[i] = 1;
        } else {
            j = i + 1;
            while (j < TSize && T[i] >= T[j]) {
                if (ans[j] == 0) {
                    break;
                }
                j = j + ans[j];
            }
            if (j < TSize && j > i && T[j] > T[i]) {
                ans[i] = j - i;
            }
        }
    }
    *returnSize = TSize;
    return ans;
}
```
