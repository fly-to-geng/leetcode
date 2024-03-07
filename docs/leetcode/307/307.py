from typing import List
import numpy as np
import random

class NumArray:

    def __init__(self, nums: List[int]):
        self.n = len(nums)
        self.nums = nums
        self.array = [0] * self.n
        for i in range(self.n):
            self.add(i, nums[i])
    
    def add(self, i: int, val: int) -> None:
        """ nums[i] + val """
        i = i + 1
        while i <= self.n:
            self.array[i - 1] += val
            i += (i & -i)
    
    def sum(self, i: int) -> int:
        """
        前 i 项和
        """
        s = 0
        i = i + 1
        while (i > 0):
            s += self.array[i - 1]
            i -= (i & -i)
        return s

    def update(self, i: int, val: int) -> None:
        """ nums[i] = val """
        addv = val - self.nums[i]
        self.add(i, addv) 
        self.nums[i] = val

    def sumRange(self, i: int, j: int) -> int:
        if i == 0:
            return self.sum(j)
        else:
            return self.sum(j) - self.sum(i - 1)
        

# 随机构造数据测试
n = 20
nums = list(np.random.randint(1, 100, n))
obj = NumArray(nums)

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
        print(obj.nums)
        print(obj.array)
        print(a, b)
    else:
        print("{} successfully.".format(i))

end = 10