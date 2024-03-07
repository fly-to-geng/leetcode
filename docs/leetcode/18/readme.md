# [18. 四数之和](https://leetcode-cn.com/problems/4sum/)

## 题目描述

给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

注意：

答案中不可以包含重复的四元组。

示例：

    给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

    满足要求的四元组集合为：
    [
      [-1,  0, 0, 1],
      [-2, -1, 1, 2],
      [-2,  0, 0, 2]
    ]

## 解题思路

固定两个数字，另外两个数字使用双指针逼近

```python
class Solution(object):
    def fourSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        sns = sorted(nums)
        n = len(sns)
        if n < 4:
            return []

        i = 0
        ans = []
        while i < n - 3:
            if i > 0 and sns[i] == sns[i-1]:
                i += 1
                continue

            j = i + 1
            while j < n - 2:
                if j > i+1 and sns[j] == sns[j-1]:
                    j += 1
                    continue
                    
                p = j + 1
                q = n - 1
                while p < q:
                    tmp = sns[p] + sns[q] + sns[i] + sns[j]
                    if tmp == target:
                        if p == j + 1 or p > j + 1 and sns[p] != sns[p-1]:
                            ans.append([sns[i],sns[j],sns[p], sns[q]])
                        p += 1
                    elif tmp < target:
                        p += 1
                    else:
                        q -= 1
                j += 1
            i += 1
        return ans

```
