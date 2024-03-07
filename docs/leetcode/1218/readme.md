# [1218. 最长定差子序列](https://leetcode-cn.com/problems/longest-arithmetic-subsequence-of-given-difference/)

## 题目描述

给你一个整数数组 arr 和一个整数 difference，请你找出 arr 中所有相邻元素之间的差等于给定 difference 的等差子序列，并返回其中最长的等差子序列的长度。

 

示例 1：

    输入：arr = [1,2,3,4], difference = 1
    输出：4
    解释：最长的等差子序列是 [1,2,3,4]。
    示例 2：

    输入：arr = [1,3,5,7], difference = 1
    输出：1
    解释：最长的等差子序列是任意单个元素。
    示例 3：

    输入：arr = [1,5,7,8,5,3,4,2,1], difference = -2
    输出：4
    解释：最长的等差子序列是 [7,5,3,1]。

## 解题思路

dp[i] 表示以 arr[i] 结尾的数组最长的等差数列长度
dp[i] = dp[j] + 1, if arr[i] - arr[j] = difference, j in [0, i - 1]
      = 1, if not find arr[j]

寻找 j 的过程需要从[i-1,0]扫描，这样只能过部分用例。使用字典记录，可以加快速度。

## AC 代码

[Python](1218.py)