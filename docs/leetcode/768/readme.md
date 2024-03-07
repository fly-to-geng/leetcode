# [768. 最多能完成排序的块 II](https://leetcode-cn.com/problems/max-chunks-to-make-sorted-ii/)

## 题目描述

这个问题和“最多能完成排序的块”相似，但给定数组中的元素可以重复，输入数组最大长度为2000，其中的元素最大为10**8。

arr是一个可能包含重复元素的整数数组，我们将这个数组分割成几个“块”，并将这些块分别进行排序。之后再连接起来，使得连接的结果和按升序排序后的原数组相同。

我们最多能将数组分成多少块？

示例 1:

      输入: arr = [5,4,3,2,1]
      输出: 1
      解释:
      将数组分成2块或者更多块，都无法得到所需的结果。
      例如，分成 [5, 4], [3, 2, 1] 的结果是 [4, 5, 1, 2, 3]，这不是有序的数组。 

示例 2:

      输入: arr = [2,1,3,4,4]
      输出: 4
      解释:
      我们可以把它分成两块，例如 [2, 1], [3, 4, 4]。
      然而，分成 [2, 1], [3], [4], [4] 可以得到最多的块数。 

注意:

      arr的长度在[1, 2000]之间。
      arr[i]的大小在[0, 10**8]之间。

## 解题思路

先排序，这样可以快速获取任何区间最大值和最小值
扫描一趟，找到排序之后的数组和未排序的数组最大值和最小值及其个数都相同的点
一旦找到，结果就增加1，更新循环变量，接着往下找

```python
class Solution(object):
    def maxChunksToSorted(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        def getMaxMin(arr):
            minv = min(arr)
            minc = arr.count(minv)
            maxv = max(arr)
            maxc = arr.count(maxv)
            return (minv, minc), (maxv, maxc)
        
        ans = 0
        i = 0
        n = len(arr)
        start = i
        sorted_arr = sorted(arr)
        while i < n:
            minv, maxv = getMaxMin(sorted_arr[start : i + 1])
            arrMin, arrMax = getMaxMin(arr[start : i + 1])
            if minv == arrMin and maxv == arrMax:
                ans += 1
                start = i + 1
            i = i + 1
        return ans
```
