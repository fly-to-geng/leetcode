# -*- coding:utf-8 -*-
from typing import List


class Solution:
 
    def convert2rank(self, nums):
        """
        返回 nums 中元素排序之后的排名，如果元素相同，排名并列
        """
        sorted_nums = sorted(nums)
        kvs = [[i, sorted_nums[i]] for i in range(len(sorted_nums))]
        for i in range(1, len(kvs)):
            if kvs[i][1] == kvs[i-1][1]:
                kvs[i][0] = kvs[i-1][0]
        dic = {}
        for k, v in kvs:
            dic[v] = k
        rank = []
        for num in nums:
            rank.append(dic[num])
        return rank
    def query(self, array, i):
        """
        返回[0, i] 维护的区间值 cnt
        """
        ans = 0
        i = i + 1
        while i > 0:
            ans += array[i - 1]
            i -= (i & -i)
        return ans
    def add(self, array, i, added):
        """
        array[i] += added 之后更新树状数组
        """
        i = i + 1
        while i <= len(array):
            array[i - 1] += added
            i += (i & -i)

    def countSmaller(self, nums: List[int]) -> List[int]:
        ans = []
        if len(nums) == 0: return ans
        nums = self.convert2rank(nums)
        n = len(nums)
        array = [0] * n
        for i in reversed(range(n)):
            cnt = self.query(array, nums[i] - 1)
            self.add(array, nums[i], 1)
            ans.insert(0, cnt)
        return ans

s = Solution()
arr = [5,2,2,6,6,1]
rank = s.convert2rank(arr)
ans = s.countSmaller(arr)
end = 10