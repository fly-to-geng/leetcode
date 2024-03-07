# [946. 验证栈序列](https://leetcode-cn.com/problems/validate-stack-sequences)

## 题目描述

给定 pushed 和 popped 两个序列，每个序列中的 值都不重复，只有当它们可能是在最初空栈上进行的推入 push 和弹出 pop 操作序列的结果时，返回 true；否则，返回 false 。

 

示例 1：

    输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
    输出：true
    解释：我们可以按以下顺序执行：
    push(1), push(2), push(3), push(4), pop() -> 4,
    push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

示例 2：

    输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
    输出：false
    解释：1 不能在 2 之前弹出。

 

提示：

    0 <= pushed.length == popped.length <= 1000
    0 <= pushed[i], popped[i] < 1000
    pushed 是 popped 的排列。

## 解题思路

1. 遍历poped中的每一个元素， 初始化 start = 0, stack = []
2. 对于poped[i], 先比较是否等于pushed[start], 如果相等，说明尚未入栈，可以入栈马上弹出， poped[i]成功匹配
   再比较是否等于栈顶的元素，如果相等，弹出栈顶元素，poped[i]成功匹配，
   否则，持续入栈直到与poped[i]相等
3. 遍历完poped之后，每个都能匹配，返回true,否则返回false


## AC代码

- [C](946.c)
- [C++](946.cpp)
- [Python](946.py)