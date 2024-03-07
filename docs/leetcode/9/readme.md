## [9. 回文数](https://leetcode-cn.com/problems/palindrome-number/)

### 题目描述

判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

**示例**

```
示例 1:

输入: 121
输出: true


示例 2:

输入: -121
输出: false
解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。


示例 3:

输入: 10
输出: false
解释: 从右向左读, 为 01 。因此它不是一个回文数。
```

### 解题思路1

使用64位数字作为容器反转int类型的数字，如果反转之后大小一样则是回文数字。

#### C++

```c
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        long int v = 0;
        long int xx = x;
        while(x)
        {
           v = v*10 + x % 10;
           x = x / 10;
        }
        if (xx == v)
        {
            return true;
        }
        
        return false;
    }
};
```

#### python

```python
class Solution:
    def isPalindrome(self, x: int) -> bool:
        if x < 0:
            return False
        xx = x
        v = 0
        while(x):
            v = v * 10 + x % 10
            x = x // 10
            
        if v == xx:
            return True
        return False
```

### 解题思路2

思路一遍历的一次才得到结果，实际上只需要遍历二分之一即可得到结果。

#### C++

```c

```

#### python

```python

```