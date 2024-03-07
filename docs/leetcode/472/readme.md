# [472. 连接词](https://leetcode-cn.com/problems/concatenated-words/)

## 题目描述

给定一个不含重复单词的列表，编写一个程序，返回给定单词列表中所有的连接词。

连接词的定义为：一个字符串完全是由至少两个给定数组中的单词组成的。

示例:

    输入: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

    输出: ["catsdogcats","dogcatsdog","ratcatdogcat"]

    解释: "catsdogcats"由"cats", "dog" 和 "cats"组成; 
        "dogcatsdog"由"dog", "cats"和"dog"组成; 
        "ratcatdogcat"由"rat", "cat", "dog"和"cat"组成。

说明:

    给定数组的元素总数不超过 10000。
    给定数组中元素的长度总和不超过 600000。
    所有输入字符串只包含小写字母。
    不需要考虑答案输出的顺序。

## 解题思路

1. 按照单词长度从小到大排序
2. 逐个单词插入前缀树，插入之前在树中查找，一旦找到从根开始插入
3. 如果能够找到，这个单词计入结果，不插入树中
4. 如果最终没能找到，把该单词插入前缀树

[C](472.c)