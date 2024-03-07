# [767. 重构字符串](https://leetcode-cn.com/problems/reorganize-string/)

## 题目描述

给定一个字符串S，检查是否能重新排布其中的字母，使得两相邻的字符不同。

若可行，输出任意可行的结果。若不可行，返回空字符串。

示例 1:

    输入: S = "aab"
    输出: "aba"

示例 2:

    输入: S = "aaab"
    输出: ""

注意:

    S 只包含小写字母并且长度在[1, 500]区间内。

## 解题思路

处理成每个字符出现的次数， 按照次数建立大顶堆。
每次取堆顶与前一次不同的元素，调整堆。
直到取完或者找不到不同的字符为止。

```python
N = 600
class Solution(object):
    def reorganizeString(self, S):
        """
        :type S: str
        :rtype: str
        """
        dic = {}
        for c in S:
            if c not in dic:
                dic[c] = 1
            else:
                dic[c] += 1
        maps = []
        for key, value in dic.iteritems():
            maps.append( [N-value, value, key] )
        heapq.heapify(maps)
        hp = maps
        ans = ""
        while (len(hp) > 0):
            index, value, key = heapq.heappop(hp)
            if len(ans) == 0 or ans[-1] != key:
                ans += key
                value = value - 1
                if value > 0:
                    heapq.heappush(hp, [N-value, value, key])
            else:
                if len(hp) == 0:
                    return ""
                index, value2, key2 = heapq.heappop(hp)
                ans += key2
                value2 = value2 - 1
                if value2 > 0:
                    heapq.heappush(hp, [N-value2, value2, key2] )
                heapq.heappush(hp, [N-value, value, key])
        return ans
```

