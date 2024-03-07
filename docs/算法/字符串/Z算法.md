# Z 算法

Z 算法也是一种字符串匹配算法，和KMP算法一样，也是预处理求出一个数组，利用求出的数组加快移动。
Z 算法需要预处理求出Z数组

## Z 数组

Z 数组中的元素Z[i] 表示从 [i...n) 的子串中是 [0...n) 前缀的长度。

```
0 1 2 3 4 5 6
a a b a a c d  <-- text
x 1 0 2 1 0 0  <-- Z Array
```

- i = 1时，`abaacd` 是 `aabaacd` 前缀的长度是 `a`, 所以 Z[1] = 1
- i = 2时，`baacd` 是 `aabaacd` 前缀的长度是 ` `,  所以 Z[2] = 0
- i = 3时，`aacd` 是 `aabaacd` 前缀的长度是 `aa`,  所以 Z[3] = 2
- i = 4时，`acd` 是 `aabaacd` 前缀的长度是 `a`,    所以 Z[4] = 1
- i = 5时，`cd` 是 `aabaacd` 前缀的长度是 ` `,     所以 Z[5] = 0
- i = 6时，`d` 是 `aabaacd` 前缀的长度是 ` `,      所以 Z[6] = 0

其他例子帮助加深理解：

```
str  = "aaaaaa"
Z[]  = {x, 5, 4, 3, 2, 1}

str = "aabaacd"
Z[] = {x, 1, 0, 2, 1, 0, 0}

str = "abababab"
Z[] = {x, 0, 6, 0, 4, 0, 2, 0}
```

## 在搜索中使用 Z 数组

设待搜索串为`T`, 模式串为`P`, `$`为在 `T` 和 `P`中都没有出现的特殊字符，
构造新的字符串`PT = P$T`, 求解出`PT` 的 Z Array.

```
P = "aab"
T = "baabaa"

0 1 2 3 4 5 6 7 8 9
a a b $ b a a b a a  <-- PT
x 1 0 0 0 3 1 0 2 1  <-- Z array
          |
          |
          V
          5  <---------- match index       
```

当求解Z Array时， 遇到长度等于模式串`P`长度的时候，记录结果。

## Z 数组求解方法

第一种方法，使用两重循环，时间复杂度时 $O(n^2)$.

```python
def getZArray(array):
    n = len(array)
    zarray = [0] * n
    for i in range(1, n):
        s1 = 0
        s2 = i
        same = 0
        while s2 < n and array[s1] == array[s2]:
            s1 += 1
            s2 += 1
            same += 1
        zarray[i] = same
    return zarray
```

我们还可以在线性时间内计算出 Z Array, 仔细分析第一种方法就能发现，从前向后计算会有很多重复计算。
我们维护一个区间[L, R] 使得 [L, R] 是整个字符串的前缀。

1. 初始化 L = 0, R = 0
2. for i in range(1, n), 
    - 2.1 如果 i > R, 利用方法一中的方法计算出 Z[i], 同时设置L = i, R = L + Z[i]
    - 2.2 如果 i <= R, k = i - L, i 右边的元素个数为 R - i + 1, 如果 Z[k] < R - i + 1, 说明 Z[i] = Z[k], 因为[L, R]已经是整个字符串的前缀。
      [L...i] == [0...k]
    - 2.3 如果  Z[k] < R - i + 1， 利用方法一重新计算Z[i], 更新L， R。

```python
def getZarr(string, z): 
    n = len(string) 
    l, r, k = 0, 0, 0
    for i in range(1, n): 
        if i > r: 
            l, r = i, i 
            while r < n and string[r - l] == string[r]: 
                r += 1
            z[i] = r - l 
            r -= 1
        else: 
            k = i - l 
            if z[k] < r - i + 1: 
                z[i] = z[k] 
            else: 
                l = i 
                while r < n and string[r - l] == string[r]: 
                    r += 1
                z[i] = r - l 
                r -= 1
    return z
```

## 算法实现

```python
# Python3 program that implements Z algorithm 
# for pattern searching 

# Fills Z array for given string str[] 
def getZarr(string, z): 
    n = len(string) 

    # [L,R] make a window which matches 
    # with prefix of s 
    l, r, k = 0, 0, 0
    for i in range(1, n): 

        # if i>R nothing matches so we will calculate. 
        # Z[i] using naive way. 
        if i > r: 
            l, r = i, i 

            # R-L = 0 in starting, so it will start 
            # checking from 0'th index. For example, 
            # for "ababab" and i = 1, the value of R 
            # remains 0 and Z[i] becomes 0. For string 
            # "aaaaaa" and i = 1, Z[i] and R become 5 
            while r < n and string[r - l] == string[r]: 
                r += 1
            z[i] = r - l 
            r -= 1
        else: 

            # k = i-L so k corresponds to number which 
            # matches in [L,R] interval. 
            k = i - l 

            # if Z[k] is less than remaining interval 
            # then Z[i] will be equal to Z[k]. 
            # For example, str = "ababab", i = 3, R = 5 
            # and L = 2 
            if z[k] < r - i + 1: 
                z[i] = z[k] 

            # For example str = "aaaaaa" and i = 2, 
            # R is 5, L is 0 
            else: 

                # else start from R and check manually 
                l = i 
                while r < n and string[r - l] == string[r]: 
                    r += 1
                z[i] = r - l 
                r -= 1

# prints all occurrences of pattern 
# in text using Z algo 
def search(text, pattern): 

    # Create concatenated string "P$T" 
    concat = pattern + "$" + text 
    l = len(concat) 

    # Construct Z array 
    z = [0] * l 
    getZarr(concat, z) 

    # now looping through Z array for matching condition 
    for i in range(l): 

        # if Z[i] (matched region) is equal to pattern 
        # length we got the pattern 
        if z[i] == len(pattern): 
            print("Pattern found at index", 
                    i - len(pattern) - 1) 

# Driver Code 
if __name__ == "__main__": 
    text = "GEEKS FOR GEEKS"
    pattern = "GEEK"
    search(text, pattern) 

# This code is conributed by 
# sanjeev2552 
```

参考文献：https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/?ref=rp

