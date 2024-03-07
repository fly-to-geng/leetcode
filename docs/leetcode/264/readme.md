# [264. 丑数 II](https://leetcode-cn.com/problems/ugly-number-ii/)

## 题目描述

编写一个程序，找出第 n 个丑数。

丑数就是质因数只包含 2, 3, 5 的正整数。

示例:

    输入: n = 10
    输出: 12
    解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
    说明:  

    1 是丑数。
    n 不超过1690。

## 解题思路

从1开始枚举，判断每个数字是否是丑数，是计数+1， 直到找到第N个丑数为止。这样到后面大量的时间就会浪费在判断是否是丑数上。

转变思路，从第一个丑数开始依次生成下一个丑数，这样无需判断是否是丑数，效率要高很多。

```python
class Solution:
    def __init__(self):
        N = 1690
        c2, c3, c5 = 0, 0, 0 # 分别指向2,3,5为因子的指针， 记录上一次的位置
        self.uglys = [1, ]
        for i in range(1, N):
            nextUgly = min(self.uglys[c2] * 2, self.uglys[c3] * 3, self.uglys[c5] * 5)
            self.uglys.append(nextUgly)

            if nextUgly == self.uglys[c2] * 2:
                c2 += 1
            if nextUgly == self.uglys[c3] * 3:
                c3 += 1
            if nextUgly == self.uglys[c5] * 5:
                c5 += 1

            print(self.uglys)
            print(c2, c3, c5)

    def nthUglyNumber(self, n: int) -> int:
        return self.uglys[n - 1]
```

分析上述过程

```
[1]
 |
 |
c2
c3
c5
 
[1, 2]
 |  |
 |  |
 c3 c2
 c5
 
[1, 2, 3]
 |  |
 |  |
 c5 c2
    c3

[1, 2, 3, 4]
 |  |  |
 |	|  |
 c5	c3 c2

[1, 2, 3, 4, 5]
    |  |
	|  |
	c3 c2
	c5

[1, 2, 3, 4, 5, 6]
    |  |  |
	|  |  |
	c5 c3 c2

[1, 2, 3, 4, 5, 6, 8]
    |  |     |
	|  |     |
   c5  c3    c2

[1, 2, 3, 4, 5, 6, 8, 9]
    |     |  |
	|     |  |
   c5     c3 c2
```

c2, c3, c5 分别表示乘 2， 3， 5 乘过的次数。
