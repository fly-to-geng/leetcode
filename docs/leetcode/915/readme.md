# [915. 分割数组](https://leetcode-cn.com/problems/partition-array-into-disjoint-intervals/)

## 题目描述

给定一个数组 A，将其划分为两个不相交（没有公共元素）的连续子数组 left 和 right， 使得：

left 中的每个元素都小于或等于 right 中的每个元素。
left 和 right 都是非空的。
left 要尽可能小。
在完成这样的分组后返回 left 的长度。可以保证存在这样的划分方法。

 

示例 1：

      输入：[5,0,3,8,6]
      输出：3
      解释：left = [5,0,3]，right = [8,6]

示例 2：

      输入：[1,1,1,0,6,12]
      输出：4
      解释：left = [1,1,1,0]，right = [6,12]
 

提示：

      2 <= A.length <= 30000
      0 <= A[i] <= 10^6
      可以保证至少有一种方法能够按题目所描述的那样对 A 进行划分。

## 解题思路

```python
class Solution:
     def partitionDisjoint(self, A):
        n = len(A)
        left_max = A[0]
        right_min = min(A[1:])
        right_count = A[1:].count(right_min)

        for i in range(1, n):
            if left_max <= right_min:
                return i
            # A[i] 加入左侧
            if A[i] > left_max:
                left_max = A[i]
            # 右侧排除 A[i]
            if A[i] == right_min:
                if right_count > 1:
                    right_count -= 1
                else:
                    right_min = min(A[i+1:])
                    right_count = A[i+1:].count(right_min)
           
        return -1
```
