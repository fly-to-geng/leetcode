# [229. 求众数 II](https://leetcode-cn.com/problems/majority-element-ii/)

## 题目描述

给定一个大小为 n 的数组，找出其中所有出现超过 ⌊ n/3 ⌋ 次的元素。

说明: 要求算法的时间复杂度为 O(n)，空间复杂度为 O(1)。

示例 1:

    输入: [3,2,3]
    输出: [3]

示例 2:

    输入: [1,1,1,3,3,2,2,2]
    输出: [1,2]

## 解题思路

超过 n/3 的数字最多只有2个， 当然也可以有一个，或者没有。

1. 使用 num1, num2 出现次数最多的两个数字， count1, count2 分别记录出现次数
2. 第一遍遍历数组， if nums[i] == num1: count1++, if nums[i] == num2: count2++
如果和num1, num2都不同， if count1 == 0: num1 = nums[i], if count2 == 0: num2 = nums[i]
如果count1, count2都不为0， count1, count2 同时 -1, 表示抵消一个。
3. 第二次遍历数组， 统计出现次数，输出出现次数大于 n/3 的数字

注意，这里 num1, num2 可能是同一个数字。

[Python](229.py)
