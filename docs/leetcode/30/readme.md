# [30. 串联所有单词的子串](https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words)

## 题目描述

给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。

注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。

 

示例 1：

    输入：
    s = "barfoothefoobarman",
    words = ["foo","bar"]
    输出：[0,9]
    解释：
    从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
    输出的顺序不重要, [9,0] 也是有效答案。

示例 2：

    输入：
    s = "wordgoodgoodgoodbestword",
    words = ["word","good","best","word"]
    输出：[]

## 解题思路

1. 统计words每个单词出现的次数
2. 遍历s, 每满足words长度就分割计算每个单词出现的次数，看是否和words计算结果相同
3. 如果相同，输出这时的起始下标

## AC代码

- [C](30.c)