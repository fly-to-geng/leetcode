# [927. 三等分](https://leetcode-cn.com/problems/three-equal-parts/)

## 题目描述

给定一个由 0 和 1 组成的数组 A，将数组分成 3 个非空的部分，使得所有这些部分表示相同的二进制值。

如果可以做到，请返回任何 [i, j]，其中 i+1 < j，这样一来：

A[0], A[1], ..., A[i] 组成第一部分；
A[i+1], A[i+2], ..., A[j-1] 作为第二部分；
A[j], A[j+1], ..., A[A.length - 1] 是第三部分。
这三个部分所表示的二进制值相等。
如果无法做到，就返回 [-1, -1]。

注意，在考虑每个部分所表示的二进制时，应当将其看作一个整体。例如，[1,1,0] 表示十进制中的 6，而不会是 3。此外，前导零也是被允许的，所以 [0,1,1] 和 [1,1] 表示相同的值。

 

示例 1：

      输入：[1,0,1,0,1]
      输出：[0,3]

示例 2：

      输出：[1,1,0,1,1]
      输出：[-1,-1]
 

提示：

      3 <= A.length <= 30000
      A[i] == 0 或 A[i] == 1

## 解题思路

基本思路是首先保证1的个数是一样的，这样才可能值是相等的。 前导0的个数可以不同。
```c
int* threeEqualParts(int* A, int ASize, int* returnSize){
    int count = 0;
    int c1;
    int i, j, right;
    int *ans;
    ans = (int*)malloc(sizeof(int) * 2);
    ans[0] = -1;
    ans[1] = -1;
    *returnSize = 2;
    for (i = 0; i < ASize; i++) {
        if (A[i] == 1) {
            count++;
        }
    }
    if (count == 0) {
        ans[0] = 0;
        ans[1] = 2;
        return ans;
    }
    if (count % 3 != 0) {
        return ans;
    }
    c1 = count / 3; // 每个值应该包含c1个1
    for (i = ASize - 1; i >= 0; i--) {
        if (A[i] == 1) {
            c1--;
        }
        if (c1 == 0) {
            right = i;
            break;
        }
    }
    // right ... ASize-1 组成的值是最终三个组都应该达到的值
    // 但是right可能不是第三组的开始，如果有0可以提前

    // 从开始找到第一个为1的位置，是否完全能和 right...ASize-1 匹配
    // 如果不能匹配，就返回false
    // 如果可以匹配，就确定了第一组的位置
    i = 0;
    while (i < ASize && A[i] == 0) {
        i++;
    } 
    j = right;
    while (i < ASize && j < ASize && A[i] == A[j]) {
        i++;
        j++;
    }
    if (j < ASize) {
        ans[0] = -1;
        ans[1] = -1;
        return ans;
    }
    // 第一组匹配上了， i 的位置就是第二组开始的位置
    ans[0] = i - 1;
    while (i < ASize && A[i] == 0) {
        i++;
    }
    j = right;
    while (i < ASize && j < ASize && A[i] == A[j]) {
        i++;
        j++;
    }
    if (j < ASize) {
        ans[0] = -1;
        ans[1] = -1;
        return ans;
    }
    if (i == right) {
        ans[1] = i;
    } else {
        ans[1] = i;
    }
    return ans;
}
```
