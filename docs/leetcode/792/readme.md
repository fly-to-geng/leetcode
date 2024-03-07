# [792. 匹配子序列的单词数](https://leetcode-cn.com/problems/number-of-matching-subsequences/)

## 题目描述

给定字符串 S 和单词字典 words, 求 words[i] 中是 S 的子序列的单词个数。

示例:
      输入: 
      S = "abcde"
      words = ["a", "bb", "acd", "ace"]
      输出: 3
      解释: 有三个是 S 的子序列的单词: "a", "acd", "ace"。

注意:

      所有在words和 S 里的单词都只由小写字母组成。
      S 的长度在 [1, 50000]。
      words 的长度在 [1, 5000]。
      words[i]的长度在[1, 50]。

## 解题思路

暴力查找

```python
class Solution(object):
    def match(self, dic, word):
        
        cur = -1
        for c in word:
            if c in dic:
                indexs = dic[c]
                flag = True
                for index in indexs:
                    if index > cur:
                        cur = index
                        flag = False
                        break
                if flag:
                    return False
            else:
                return False
        return True
    def numMatchingSubseq(self, S, words):
        """
        :type S: str
        :type words: List[str]
        :rtype: int
        """
        ans = 0
        dic = {}
        for i, c in enumerate(S):
            if c not in dic:
                dic[c] = [i]
            else:
                dic[c].append(i)
        for word in words:
            if self.match(dic, word):
                ans += 1
        return ans
```
