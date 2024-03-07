# [1048. 最长字符串链](https://leetcode-cn.com/problems/longest-string-chain/)

## 题目描述

给出一个单词列表，其中每个单词都由小写英文字母组成。

如果我们可以在 word1 的任何地方添加一个字母使其变成 word2，那么我们认为 word1 是 word2 的前身。例如，"abc" 是 "abac" 的前身。

词链是单词 [word_1, word_2, ..., word_k] 组成的序列，k >= 1，其中 word_1 是 word_2 的前身，word_2 是 word_3 的前身，依此类推。

从给定单词列表 words 中选择单词组成词链，返回词链的最长可能长度。
 

示例：

        输入：["a","b","ba","bca","bda","bdca"]
        输出：4
        解释：最长单词链之一为 "a","ba","bda","bdca"。
 

提示：

        1 <= words.length <= 1000
        1 <= words[i].length <= 16
        words[i] 仅由小写英文字母组成。

## 解题思路

如果当前档次的长度是 m, 那么下一个可能是词链的单词长度是 m + 1, 搜索所有长度是 m + 1的单词， 记录最大值。

```python
class Solution(object):
    def longestStrChain(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        def is_prefix(word, word2):
            if len(word)+1 != len(word2):
                return False
            count = 1 # 最多出现一次字符不匹配
            i = 0
            j = 0
            while i < len(word) and j < len(word2):
                if word[i] == word2[j]:
                    i += 1
                    j += 1
                elif count > 0:
                    count -= 1
                    j += 1
                else:
                    return False
            return True
            
        dic = {}
        minl = 16
        maxl = 1
        for word in words:
            l = len(word)
            minl = min([minl, l])
            maxl = max([maxl, l])
            if l not in dic:
                dic[l] = [[word, 1]]
            else:
                dic[l].append([word, 1])
        
        l = minl
        longest = 1
        while l <= maxl:
            if l in dic and l+1 in dic:
                for word in dic[l]:
                    for i in  range(len(dic[l+1])):
                        ans = is_prefix(word[0], dic[l+1][i][0])
                        #print("{0} is {1} ? {2}".format(word[0], dic[l+1][i][0], ans))
                        if ans:
                            dic[l+1][i][1] = word[1] + 1
                            longest = max([longest, dic[l+1][i][1]])
            l += 1

        return longest
```