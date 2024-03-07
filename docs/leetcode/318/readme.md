# [318. 最大单词长度乘积](https://leetcode-cn.com/problems/maximum-product-of-word-lengths/)

## 题目描述

给定一个字符串数组 words，找到 length(word[i]) * length(word[j]) 的最大值，并且这两个单词不含有公共字母。你可以认为每个单词只包含小写字母。如果不存在这样的两个单词，返回 0。

示例 1:

    输入: ["abcw","baz","foo","bar","xtfn","abcdef"]
    输出: 16 
    解释: 这两个单词为 "abcw", "xtfn"。

示例 2:

    输入: ["a","ab","abc","d","cd","bcd","abcd"]
    输出: 4 
    解释: 这两个单词为 "ab", "cd"。

示例 3:

    输入: ["a","aa","aaa","aaaa"]
    输出: 0 
    解释: 不存在这样的两个单词。

## 解题思路

把单词转换成数字，利用与运算判断有没有相同的字母。

```python
class Solution(object):
    def maxProduct(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        bits = []
        for word in words:
            b = 0
            for c in word:
                b = b | ( 1 << (ord(c) - ord('a')) )
            bits.append(b)

        ans = 0
        for i in range(len(bits)):
            for j in range(len(bits)):
                if i != j and bits[i] & bits[j] == 0:
                    ab = len(words[i]) * len(words[j])
                    ans = max([ans, ab])

        return ans
```
