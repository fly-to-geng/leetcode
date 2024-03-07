# [1031. 两个非重叠子数组的最大和](https://leetcode-cn.com/problems/maximum-sum-of-two-non-overlapping-subarrays/)

## 题目描述

给出非负整数数组 A ，返回两个非重叠（连续）子数组中元素的最大和，子数组的长度分别为 L 和 M。（这里需要澄清的是，长为 L 的子数组可以出现在长为 M 的子数组之前或之后。）

从形式上看，返回最大的 V，而 V = (A[i] + A[i+1] + ... + A[i+L-1]) + (A[j] + A[j+1] + ... + A[j+M-1]) 并满足下列条件之一：

 

0 <= i < i + L - 1 < j < j + M - 1 < A.length, 或
0 <= j < j + M - 1 < i < i + L - 1 < A.length.
 

示例 1：

        输入：A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
        输出：20
        解释：子数组的一种选择中，[9] 长度为 1，[6,5] 长度为 2。

示例 2：

        输入：A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
        输出：29
        解释：子数组的一种选择中，[3,8,1] 长度为 3，[8,9] 长度为 2。

示例 3：

        输入：A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
        输出：31
        解释：子数组的一种选择中，[5,6,0,9] 长度为 4，[0,3,8] 长度为 3。
 

提示：

        L >= 1
        M >= 1
        L + M <= A.length <= 1000
        0 <= A[i] <= 1000

## 解题思路

先求出数组的前缀和，然后固定一个数组， 求另一个数组的最大和，
遍历每一个固定的数组，即可找出所有最大的解，最后取最大的那个。
注意边界条件的确定。

```c++
#define MAX(a, b) ((a) > (b)) ? (a) : (b)
int getMSum(int *A, int *aSum, int ASize, int i, int L, int M)
{
    int lefts = 0;
    int lefte = i - 1;
    int rights = i + L;
    int righte = ASize - 1;
    int maxv = -1;
    int j, tmp;

    if (lefte - lefts + 1 >= M) {
        for (j = lefts; j <= lefte - M + 1; j++) {
            tmp = aSum[j + M] - aSum[j];
            maxv = MAX(maxv, tmp);
        }
    }

    if (righte - rights + 1 >= M) {
        for (j = rights; j <= righte - M + 1; j++) {
            tmp = aSum[j + M] - aSum[j];
            maxv = MAX(maxv, tmp);
        }
    }
    return maxv;
}
int maxSumTwoNoOverlap(int* A, int ASize, int L, int M){
    int *aSum;
    int lSum = 0;
    int mSum = 0;
    int sum = 0;
    int ans = 0;
    int i, j;

    if (A == NULL || ASize == 0) {
        return 0;
    }

    /* 求前缀和 */
    aSum = (int*)malloc(sizeof(int) * (ASize + 1));
    aSum[0] = 0;
    for (i = 0; i < ASize; i++) {
        aSum[i + 1] = aSum[i] + A[i];
    }

    /* 确定L，寻找可能的最大的M */
    for (i = 0; i <= ASize - L; i++) {
        lSum = aSum[i + L] - aSum[i];
        mSum = getMSum(A, aSum, ASize, i, L, M);
        sum = lSum + mSum;
        ans = MAX(ans, sum);
    }
    return ans;
}
```