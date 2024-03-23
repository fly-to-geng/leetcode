from typing import List
import numpy as np
import random

class Node:
    def __init__(self, left=None, right=None, begin=-1, end=-1, value=0):
        self.left = left
        self.right = right
        self.begin = begin
        self.end = end
        self.value = value

class NumArray:

    def __init__(self, nums: List[int]):
        self.root = None
        self.array = nums
        self.root = self.create(nums)

    def create(self, array):
        """
        创建线段树，维护区间和
        """
        def __create(begin, end):
            if begin > end:
                return None
            if begin == end:
                node = Node(begin=begin, end=end, value=array[begin])
                return node
            mid = (begin + end) // 2
            node = Node(begin=begin, end=end)
            node.left = __create(begin, mid)
            node.right = __create(mid+1, end)
            node.value = node.left.value + node.right.value
            return node

        n = len(array)
        begin, end = 0, n - 1
        self.root = __create(begin, end)
        self.array = array
        return self.root

    def sumRange(self, i: int, j: int) -> int:
        return self.query(i, j)

    def query(self, begin, end):
        """
        查询区间[begin, end]的和
        """
        def __query(node, begin, end):
            if begin <= node.begin and end >= node.end:
                return node.value
            if begin > node.end or end < node.begin:
                return 0
            lres = __query(node.left, begin, end)
            rres = __query(node.right, begin, end)
            return lres + rres
        return __query(self.root, begin, end)

    def add(self, i, x):
        """
        array[i] + x 之后更新线段树维护的值
        """
        def __add(node, i, x):
            if node.begin == node.end == i:
                node.value += x
                return
            node.value += x
            mid = (node.begin + node.end) // 2
            if i <= mid:
                __add(node.left, i, x)
            else:
                __add(node.right, i, x)
        __add(self.root, i, x)
        return self.root
    
    def update(self, i: int, val: int) -> None:
        """
        array[i] = x 之后更新线段树维护的值
        """
        added = val - self.array[i]
        self.add(i, added)
        self.array[i] = val
        return self.root


# 随机构造数据测试
n = 8
nums = list(np.random.randint(1, 10, n))
obj = NumArray(nums)
root = obj.create(nums)

count = 50
for i in range(count):
    index = random.randint(0, n-1)
    val = random.randint(1, 200)
    obj.update(index, val)
    nums[index] = val

    a = random.randint(0, n-1)
    b = random.randint(a, n-1)
    sumab = obj.sumRange(a, b)
    expect = sum(nums[a:b+1])
    if sumab != expect:
        print(nums)
        print(a, b)
    else:
        print("{} successfully.".format(i))

end = 10