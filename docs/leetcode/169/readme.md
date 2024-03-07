# [169. 多数元素](https://leetcode-cn.com/problems/majority-element/)

## 题目描述

给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

 

示例 1:

    输入: [3,2,3]
    输出: 3

示例 2:

    输入: [2,2,1,1,1,2,2]
    输出: 2

## 解题思路

1. 使用 currNum 记录当前出现次数最多的数字， 使用 count 记录出现的次数。
2. 遍历数组第一遍， 如果遇到 currNum, count++, 如果遇到不是 currNum, count--.
如果 count == 0, currNum 设置成新的元素， count = 1.
3. 遍历数组第二遍， 统计currNum 出现的次数

[Python](169.py)