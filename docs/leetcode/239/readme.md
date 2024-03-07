# [239. 滑动窗口最大值](https://leetcode-cn.com/problems/sliding-window-maximum/)

## 题目描述

给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回滑动窗口中的最大值。

 

进阶：

你能在线性时间复杂度内解决此题吗？

 

示例:

    输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
    输出: [3,3,5,5,6,7] 
    解释: 

      滑动窗口的位置                最大值
    ---------------               -----
    [1  3  -1] -3  5  3  6  7       3
     1 [3  -1  -3] 5  3  6  7       3
     1  3 [-1  -3  5] 3  6  7       5
     1  3  -1 [-3  5  3] 6  7       5
     1  3  -1  -3 [5  3  6] 7       6
     1  3  -1  -3  5 [3  6  7]      7
 

提示：

    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4
    1 <= k <= nums.length

## 解题思路


### 方法一

暴力解决方法， 滑动窗口， 每次滑出一个，滑入一个， 看滑出的是否是最大值，如果滑出的不是最大值，比较滑入元素和最大值可以得到新的最大值； 如果滑出的是最大值， 新的最大值只能遍历一遍得到，这里会导致时间复杂度不是线性的。
最坏的情况，每次都需要遍历得到最大值, 时间复杂度是 O(k) * (n - k)。

```python
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        maxv = max(nums[0:k])
        ans = [maxv]
        for i in range(1, n - k + 1):
            if nums[i - 1] != maxv:
                if nums[i + k - 1] > maxv:
                    maxv = nums[i + k - 1]
            else:
                maxv = max(nums[i: i + k])
            ans.append(maxv)
        return ans
 ```
 
 ### 方法二
 
 如果使用大小为K的堆，每次建立堆 O(K), 取出最大值 O(1), 循环 n-k+1 次， 总的时间复杂度是 nk, 与暴力方法的复杂度一样，但是最后一个用例过不了。
 
 ```python
 import heapq
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        MAX_NUM = 100
        n = len(nums)
        ans = []
        for i in range(n - k + 1):
            heap = [(MAX_NUM - num, num) for num in nums[i : i + k]]
            heapq.heapify(heap)
            ans.append(heapq.heappop(heap)[1])
        return ans
 ```
 
 17/18 cases passed (N/A)
 
 ### 方法三
 
 使用双向队列， 在队列首维护最大值的索引， 始终保持队列的降序排列。
 
 ```python
 from collections import deque
from typing import List

class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        if n * k == 0: return []
        if k == 1: return nums

        
        # 创建一个双向队列， 我们用队列头 array[0] 的位置存储当前滑动窗口最大值的索引
        # 队列从左向右存储当前滑动窗口内元素的索引值，但是并不存储所有的值， 保持降序存储
        # 在队列尾添加元素的时候， 首先把应该弹出的元素都弹出
        # 应该弹出的元素包括， 1. 滑动出窗口的元素； 2. 比将要加入的元素小的元素
        array = deque()
        maxIndex = 0
        for i in range(k):
            # array 非空的时候首先弹出比 nums[i] 小的元素
            if array:
                while array and nums[ array[-1] ] < nums[i]:
                    array.pop()
            # 从队尾加入队列
            array.append(i)
            if nums[i] > nums[maxIndex]:
                maxIndex = i
        ans = [ nums[maxIndex] ]

        # 处理元素 [k, n-1]
        for i in range(k, n):
            # 如果队首的元素已经位于滑动窗口之外了，弹出它
            # 这里无需循环弹出是因为一次只加入一个
            if array and array[0] == i - k:
                array.popleft()
            while array and nums[ array[-1] ] < nums[i]:
                array.pop()
            array.append(i)
            ans.append(nums[ array[0] ])
        return ans
 ```
 
 ### 方法四
 
 使用分割区域的前向和后向数组
 
 ```python
 class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        if n * k == 0: return []
        if k == 1: return nums

        # k = 3, n = 10
        # 3, 1, 6 | 4, 8, 2 | 1, 9, 10 | 7
        # 3, 3, 6 | 4, 8, 8 | 1, 9, 10 | 7  --> left
        # 6, 6, 6 | 8, 8, 2 | 10, 10, 10| 7 --> right
        # left[i] 表示 [(i / k) * k, i] 区间的最大值
        # right[i] 表示 [i, (i/k + 1)*k - 1] 区间的最大值
        # 设 [i, j] 为区间大小为 k 的区间， 则该区间的最大值
        # 如果 i = (i / k) * k, j = (i/k + 1)*k - 1, 正好位于区间内，max([i, j]) = left[j] = right[i]
        # 如果 [i, j] 跨越 k 区间， 例如 i = 1, j = 3, 则 max([1, 3]) = max( max([1,2]) , max([3,3]) )
        # 而 max([1, 2]) = right[i], max([3,3]) = left[j]
        # 综上， 最后的结果总是等于 max(left[j], right[i])
        left = [0] * n
        for i in range(n):
            if i % k == 0:
                left[i] = nums[i]
            else:
                if nums[i] > left[i - 1]:
                    left[i] = nums[i]
                else:
                    left[i] = left[i - 1]
        
        right = [0] * n
        for i in reversed(range(n)):
            if (i + 1) % k == 0:
                right[i] = nums[i]
            else:
                if i + 1 >= n:
                    right[i] = nums[i]
                    continue
                if nums[i] > right[i + 1]:
                    right[i] = nums[i]
                else:
                    right[i] = right[i + 1]
        
        ans = []
        for i in range(n - k + 1):
            j = i + k - 1
            maxv = max(right[i], left[j])
            ans.append(maxv)
        return ans
 ```
