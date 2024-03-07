# [515. 在每个树行中找最大值](https://leetcode-cn.com/problems/find-largest-value-in-each-tree-row/)

## 题目描述

您需要在二叉树的每一行中找到最大的值。

示例：

    输入: 

              1
             / \
            3   2
           / \   \  
          5   3   9 

    输出: [1, 3, 9]

## 解题思路

层次遍历二叉树，每个层求一个最大值， 层次的区分使用队列。

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def largestValues(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        ans = []
        if root is None:
            return ans
        count = 1
        deque = []
        
        deque.append(root)
        ans.append(root.val)
        while len(deque) > 0:
            cur = deque.pop(0)
            if cur.left:
                deque.append(cur.left)
            if cur.right:
                deque.append(cur.right)
            count -= 1
            if count == 0 and len(deque) > 0:
                ans.append( max([node.val for node in deque]) )
                count = len(deque)
        return ans
```
