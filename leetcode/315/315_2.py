# -*- coding:utf-8 -*-
from typing import List

class Node:
    def __init__(self, left=None, right=None, begin=None, end=None, val=None):
        self.left = left
        self.right = right
        self.begin = begin
        self.end = end
        self.val = val
class Solution:
    def build(self, begin, end):
        """
        构造范围为 [beign, end] 的线段树
        """
        if begin == end:
            node = Node(begin=begin, end=end)
            node.val = 0
            return node
        mid = (begin + end) // 2
        node = Node(begin=begin, end=end)
        node.left = self.build(begin, mid)
        node.right = self.build(mid+1, end)
        node.val = 0
        return node
    def query(self, node, begin, end):
        """
        查询 [begin, end] 区间的 cnt 值
        """
        if begin > node.end or end < node.begin:
            return 0
        if begin <= node.begin and end >= node.end:
            return node.val
        lres = self.query(node.left, begin, end)
        rres = self.query(node.right, begin, end)
        return lres + rres
    def add(self, node, idx, addv):
        """
        区间 [idx, idx] 增加 addv
        """
        if node.begin == node.end == idx:
            node.val += addv
            return
        mid = (node.begin + node.end) // 2
        node.val += addv
        if idx <= mid:
            self.add(node.left, idx, addv)
        else:
            self.add(node.right, idx, addv)
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
    def countSmaller(self, nums: List[int]) -> List[int]:
        ans = []
        if len(nums) == 0: return ans
        nums = self.convert2rank(nums)
        low, high = min(nums), max(nums)
        root = self.build(low, high)
        for num in reversed(nums):
            cnt = self.query(root, low, num-1)
            ans.insert(0, cnt)
            self.add(root, num, 1)
        return ans

s = Solution()
arr = [5,2,2,6,6,1]
rank = s.convert2rank(arr)
ans = s.countSmaller(arr)
end = 10