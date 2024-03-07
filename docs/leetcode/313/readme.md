# [313. 超级丑数](https://leetcode-cn.com/problems/super-ugly-number/)

## 题目描述

编写一段程序来查找第 n 个超级丑数。

超级丑数是指其所有质因数都是长度为 k 的质数列表 primes 中的正整数。

示例:

    输入: n = 12, primes = [2,7,13,19]
    输出: 32 
    解释: 给定长度为 4 的质数列表 primes = [2,7,13,19]，前 12 个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32] 。
    说明:

    1 是任何给定 primes 的超级丑数。
     给定 primes 中的数字以升序排列。
    0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000 。
    第 n 个超级丑数确保在 32 位有符整数范围内。

## 解题思路

idx 有 len(primes) 个元素， 初始化为0， 为对应的 primes[i] 的指针。思路与 [264. 丑数 II]() 完全一致。

```python
class Solution:
    def nthSuperUglyNumber(self, n: int, primes: List[int]) -> int:
        k = len(primes)
        idx = [0] * k # 指示primes[i]当前位置
        array = [1]
        for _ in range(1, n):
            nextNumbers = [array[value] * primes[i] for i, value in enumerate(idx)]
            nextNumber = min(nextNumbers)
            array.append(nextNumber)
            for j in range(k):
                if array[ idx[j] ] * primes[j] == nextNumber:
                    idx[j] += 1
        return array[n-1]
```
