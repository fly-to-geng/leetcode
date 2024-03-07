# [1423. 可获得的最大点数](https://leetcode-cn.com/problems/maximum-points-you-can-obtain-from-cards/)

## 题目描述

几张卡牌 排成一行，每张卡牌都有一个对应的点数。点数由整数数组 cardPoints 给出。

每次行动，你可以从行的开头或者末尾拿一张卡牌，最终你必须正好拿 k 张卡牌。

你的点数就是你拿到手中的所有卡牌的点数之和。

给你一个整数数组 cardPoints 和整数 k，请你返回可以获得的最大点数。

 

示例 1：

      输入：cardPoints = [1,2,3,4,5,6,1], k = 3
      输出：12
      解释：第一次行动，不管拿哪张牌，你的点数总是 1 。但是，先拿最右边的卡牌将会最大化你的可获得点数。最优策略是拿右边的三张牌，最终点数为 1 + 6 + 5 = 12 。

示例 2：

    输入：cardPoints = [2,2,2], k = 2
    输出：4
    解释：无论你拿起哪两张卡牌，可获得的点数总是 4 。

示例 3：

    输入：cardPoints = [9,7,7,9,7,7,9], k = 7
    输出：55
    解释：你必须拿起所有卡牌，可以获得的点数为所有卡牌的点数之和。

示例 4：

    输入：cardPoints = [1,1000,1], k = 1
    输出：1
    解释：你无法拿到中间那张卡牌，所以可以获得的最大点数为 1 。 

示例 5：

    输入：cardPoints = [1,79,80,1,1,1,200,1], k = 3
    输出：202
 

提示：

    1 <= cardPoints.length <= 10^5
    1 <= cardPoints[i] <= 10^4
    1 <= k <= cardPoints.length

## 解题思路

```c

#define NN 100000

int **matrix = NULL;
int *colSize = NULL;
int n = 0;

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
    return 0;
}
void iter(int i, int j, int *ans, int *ansEnd)
{
    while (i >= 0) {
        if (j < colSize[i]) {
			ans[(*ansEnd)++] = matrix[i][j];
		}
        i -= 1;
        j += 1;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDiagonalOrder(int** nums, int numsSize, int* numsColSize, int* returnSize){
    int m = 0;
    int i, j, k;
    
    for (i = 0; i < numsSize; i++) {
        m = max(m, numsColSize[i]);
    }
    
    int *ans = (malloc(sizeof(int) * NN));
    int ansEnd = 0;
    matrix = nums;
    n = numsSize;
    colSize = numsColSize;
    
    for (i = 0; i < numsSize - 1; i++) {
        iter(i, 0, ans, &ansEnd);
    }
    
    for (j = 0; j < m; j++) {
        iter(numsSize - 1, j, ans, &ansEnd);
    }
    
    *returnSize = ansEnd;
    return ans;
}
```
