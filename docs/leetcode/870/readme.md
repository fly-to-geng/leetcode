# [870. 优势洗牌](https://leetcode-cn.com/problems/advantage-shuffle/)

## 题目描述

给定两个大小相等的数组 A 和 B，A 相对于 B 的优势可以用满足 A[i] > B[i] 的索引 i 的数目来描述。

返回 A 的任意排列，使其相对于 B 的优势最大化。

 

示例 1：

      输入：A = [2,7,11,15], B = [1,10,4,11]
      输出：[2,11,7,15]

示例 2：

      输入：A = [12,24,8,32], B = [13,25,32,11]
      输出：[24,32,8,12]
 

提示：

      1 <= A.length = B.length <= 10000
      0 <= A[i] <= 10^9
      0 <= B[i] <= 10^9

## 解题思路

贪心法解题，先把A排序，遍历B中每个元素，从A中找到刚好大于它的最小元素放入结果中，如果没有大于的元素，就选择一个最小的元素放进去。

两层循环，时间复杂度较高，无法通过所有的用例。(59 / 67 个通过测试用例)

```c
class Solution(object):
    def advantageCount(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: List[int]
        """
        A = sorted(A)

        ans = []
        for i in range(len(B)):
            find = False
            for j in range(len(A)):
                if A[j] > B[i]:
                    ans.append(A[j])
                    del A[j]
                    find = True
                    break
            if not find:
                ans.append(A[0])
                del A[0]
        return ans
```

优化查找过程，使用二分查找加快速度，可以通过所有的用例

```python
class Solution(object):
    def advantageCount(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: List[int]
        """
        def find(number):
            """
            找到A中第一个大于number的数字的下标
            如果没有找到，返回A中最小数字的下标
            """
            n = len(A)
            left = 0
            right = n - 1
            while left <= right:
                mid = (left + right) // 2
                if A[mid] > number:
                    right = mid - 1
                else:
                    left = mid + 1
            if left < n and A[left] > number:
                return left
            else:
                return 0
            
        A = sorted(A)

        ans = []
        for i in range(len(B)):
            index = find(B[i])
            #print("{0} {1} {2}\n".format(A[index], B[i], index))
            ans.append(A[index])
            del A[index]

        return ans
```
