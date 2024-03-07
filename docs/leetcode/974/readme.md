# [974. 和可被 K 整除的子数组](https://leetcode-cn.com/problems/subarray-sums-divisible-by-k/)

## 题目描述

给定一个整数数组 A，返回其中元素之和可被 K 整除的（连续、非空）子数组的数目。

示例：

    输入：A = [4,5,0,-2,-3,1], K = 5
    输出：7
    解释：
    有 7 个子数组满足其元素之和可被 K = 5 整除：
    [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
 

提示：

    1 <= A.length <= 30000
    -10000 <= A[i] <= 10000
    2 <= K <= 10000

## 解题思路

统计前缀和， 利用哈希表计算前缀和数组对K取余之后剩下的值， 记录每个值出现的次数。

```c
#define N 10001
int hashMap[N];
void init()
{
    int i;
    for (i = 0; i < N; i++) {
        hashMap[i] = 0;
    }
}
int subarraysDivByK(int* A, int ASize, int K){
    int *sums;
    int i;
    int ans = 0;

    sums = (int*)malloc(sizeof(int) * ASize);
    sums[0] = A[0];
    for (i = 1; i < ASize; i++) {
        sums[i] = sums[i - 1] + A[i];
    }
    init();
    for (i = 0; i < ASize; i++) {
        sums[i] = (sums[i] % K + K) % K;
        hashMap[sums[i]]++;
        if (sums[i] == 0) {
            ans++;
        }
    }
    for (i = 0; i < N; i++) {
        if (hashMap[i] != 0) {
            ans += hashMap[i] * (hashMap[i] - 1) / 2;
        }
    }
    return ans;
}
```
