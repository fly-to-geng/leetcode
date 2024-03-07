# [307. 区域和检索 - 数组可修改](https://leetcode-cn.com/problems/range-sum-query-mutable/)

## 题目描述

给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。

update(i, val) 函数可以通过将下标为 i 的数值更新为 val，从而对数列进行修改。

示例:

    Given nums = [1, 3, 5]

    sumRange(0, 2) -> 9
    update(1, 2)
    sumRange(0, 2) -> 8

说明:

    数组仅可以在 update 函数下进行修改。
    你可以假设 update 函数与 sumRange 函数的调用次数是均匀分布的。

## 解题思路

## AC代码

- [python](307.py) 树状数组实现
- [C](307_3.c)

- [python](307_2.py) 线段树实现
- [C](307.c)