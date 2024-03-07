# -*- coding:utf-8 -*-
from typing import List

class Solution:
    def merge(self, array, begin, mid, end, ans):
        left_array = array[begin : mid + 1]
        right_array = array[mid + 1 : end + 1]
        i, j = 0, 0
        m, n = mid - begin + 1, end - mid
        for k in range(begin, end + 1):
            if i < m and j < n and left_array[i][0] <= right_array[j][0]:
                ans[left_array[i][1]] += j # 记录右侧比自己小的元素个数
                array[k] = left_array[i]
                i += 1
            elif i < m and j < n and left_array[i][0] > right_array[j][0]:
                array[k] = right_array[j]
                j += 1
            elif i < m:
                ans[left_array[i][1]] += j # 记录右侧比自己小的元素个数
                array[k] = left_array[i]
                i += 1
            else:
                array[k] = right_array[j]
                j += 1

    def mergesort(self, array, begin, end, ans):
        if begin >= end:
            return
        mid = (begin + end) // 2
        self.mergesort(array, begin, mid, ans)
        self.mergesort(array, mid + 1, end, ans)
        self.merge(array, begin, mid, end, ans)
        
    def countSmaller(self, nums: List[int]) -> List[int]:
        index_nums = [ (nums[i], i) for i in range(len(nums))]
        ans = [0] * len(nums)
        self.mergesort(index_nums, 0, len(index_nums) - 1, ans)
        return ans

s = Solution()
arr = [5,2,2,6,6,1]
ans = s.countSmaller(arr)
end = 10