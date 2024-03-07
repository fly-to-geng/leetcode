# [336. 回文对](https://leetcode-cn.com/problems/palindrome-pairs/)

## 题目描述

给定一组唯一的单词， 找出所有不同 的索引对(i, j)，使得列表中的两个单词， words[i] + words[j] ，可拼接成回文串。

示例 1:

    输入: ["abcd","dcba","lls","s","sssll"]
    输出: [[0,1],[1,0],[3,2],[2,4]] 
    解释: 可拼接成的回文串为 ["dcbaabcd","abcddcba","slls","llssssll"]

示例 2:

    输入: ["bat","tab","cat"]
    输出: [[0,1],[1,0]] 
    解释: 可拼接成的回文串为 ["battab","tabbat"]

## 解题思路

1. 暴力方法

```python
class Solution:
    def palindromePairs(self, words: List[str]) -> List[List[int]]:
        def valid(string):
            m = len(string)
            left, right = 0, m-1
            while left < right:
                if string[left] != string[right]:
                    return False
                left += 1
                right -= 1
            return True
            
        n = len(words)
        ans = []
        for i in range(n):
            for j in range(n):
                if i != j:
                    string = words[i] + words[j]
                    if valid(string):
                        ans.append([i, j])
        return ans
```
