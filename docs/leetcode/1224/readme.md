# [1224. 最大相等频率](https://leetcode-cn.com/problems/maximum-equal-frequency/)

## 题目描述

给出一个正整数数组 nums，请你帮忙从该数组中找出能满足下面要求的 最长 前缀，并返回其长度：

从前缀中 删除一个 元素后，使得所剩下的每个数字的出现次数相同。
如果删除这个元素后没有剩余元素存在，仍可认为每个数字都具有相同的出现次数（也就是 0 次）。


示例 1：

        输入：nums = [2,2,1,1,5,3,3,5]
        输出：7
        解释：对于长度为 7 的子数组 [2,2,1,1,5,3,3]，如果我们从中删去 nums[4]=5，就可以得到 [2,2,1,1,3,3]，里面每个数字都出现了两次。

示例 2：

        输入：nums = [1,1,1,2,2,2,3,3,3,4,4,4,5]
        输出：13

示例 3：

        输入：nums = [1,1,1,2,2,2]
        输出：5

示例 4：

输入：nums = [10,2,8,9,3,8,1,5,2,3,7,6]
输出：8
 

提示：

        2 <= nums.length <= 10^5
        1 <= nums[i] <= 10^5

## 解题思路

思路：
1. 维护两个map, 一个是num --> count, 记录每种数字出现的次数，一个是count --> num, 表示出现次数为count的数字都有哪些。
2. 遍历一遍数组，计算出两个map, 然后从后向前遍历一遍。
3. 对于每一个i, 检查nums[0:i+1]是否满足要求，如果满足，返回 i + 1, 如果不满足，删除nums[i], 更新两个map.

该思路有两个关键逻辑：
1. 如何通过两个map判断是否满足题目要求
2. 删除一个数字之后，如何更新两个map

```python
class Solution(object):
    def maxEqualFreq(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def check(num2count, count2num, current):
            """
            检查是否满足删除一个数字之后，剩下的数字出现次数都相同
            """
            # count 出现3种以上的情况，删除一个至少还有2种情况
            if len(count2num) > 2:
                return False
            # 如果所有的数字都出现一次，可以满足删除一个数字之后出现的次数相等
            if len(count2num) == 1 and count2num.keys()[0] == 1:
                return True
            # 如果所有数字都出现了相同次数，且只有一种数字，可以满足删除一个之后剩下的出现次数还一样
            if len(count2num) == 1 and len(num2count) == 1:
                return True
            # 否则，所有的数字出现次数相等且不是都出现了一次，无法满足删除一个数字之后出现的次数都相等
            if len(count2num) <= 1:
                return False
            key1, key2 = count2num.keys()
            if key1 > key2:
                key1, key2 = key2, key1
            # 如果只有两种出现频率，其中出现一次的只有一个数字，去掉该数字之后，剩下的出现频率都相等
            if len(count2num[key1]) == 1 and key1 == 1:
                return True
            # 如果只有两种出现频率且只差1， 出现频率大的只有一种数字，那么可以删除一个该数字，这样剩下的所有数字出现次数相同
            if key2-key1==1 and len(count2num[key2]) == 1:
                return True
            return False

        num2count = {}
        count2num = {}

        # 统计每种数字的出现次数
        for i, num in enumerate(nums):
            if num not in num2count:
                num2count[num] = 1
            else:
                num2count[num] += 1

        # 记录每种出现次数都有哪些数字
        for key, value in num2count.iteritems():
            if value not in count2num:
                count2num[value] = [key]   
            else:
                count2num[value].append(key)
        
        # 检查是否符合要求，然后去掉 i
        for i in reversed(range(len(nums))):
            if check(num2count, count2num, nums[i]) == True:
                return i + 1
            # 删除 nums[i], 更新两个 map
            if nums[i] in num2count:
                count = num2count[ nums[i] ]
                if count > 1:
                    num2count[ nums[i] ] -= 1
                else:
                    del num2count[ nums[i] ]

                if len(count2num[count]) == 1:
                    del count2num[count]
                else:
                    count2num[count].remove(nums[i])
                if count > 1:
                    count = count - 1
                    if count not in count2num:
                        count2num[count] = [nums[i]]
                    else:
                        count2num[count].append(nums[i])
        return 0
```
