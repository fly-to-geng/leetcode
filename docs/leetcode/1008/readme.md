# [1008. 先序遍历构造二叉树](https://leetcode-cn.com/problems/construct-binary-search-tree-from-preorder-traversal/)

## 题目描述

返回与给定先序遍历 preorder 相匹配的二叉搜索树（binary search tree）的根结点。

(回想一下，二叉搜索树是二叉树的一种，其每个节点都满足以下规则，对于 node.left 的任何后代，值总 < node.val，而 node.right 的任何后代，值总 > node.val。此外，先序遍历首先显示节点的值，然后遍历 node.left，接着遍历 node.right。）

 

示例：

        输入：[8,5,1,7,10,12]
        输出：[8,5,10,1,7,null,12]

![](tree.png) 

提示：

        1 <= preorder.length <= 100
        先序 preorder 中的值是不同的。

## 解题思路

二叉搜索树的中序遍历序列是有序的，所以可以先排序获取中序遍历序列， 再结合先序遍历序列生成二叉树。

第二种思路， 直接根据二叉搜索树的性质构造。 先序遍历序列一定是根在最前面， 确定了根，所有小于根的应该都在左子树，所有大于根的应该都在右子树。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* bstFromPreorder2(int* preorder, int start, int end){
    int i;
    int left_start = -1;
    int left_end = -2;
    int right_start = -1;
    int right_end = -2;

    // 空数组返回
    if (preorder == NULL) {
        return NULL;
    }
    // 长度为0返回
    if (end - start + 1 <= 0) {
        return NULL;
    }
    // 第一个结点作为根结点，所有比它小的为做子树，所有比它大的为右子树
    struct TreeNode* root;
    root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = preorder[start];

    i = start + 1;
    left_start = start + 1;
    while (i <= end) {
        if (preorder[i] > preorder[start]) {
            left_end = i - 1;
            right_start = i;
            right_end = end;
            break;
        }
        // 如果没有右子树
        if (i == end) {
            left_end = end;
            break;
        }
        i++;
    }
    root->left = bstFromPreorder2(preorder, left_start, left_end);
    root->right = bstFromPreorder2(preorder, right_start, right_end);
    return root;
}
struct TreeNode* bstFromPreorder(int* preorder, int preorderSize){
    return bstFromPreorder2(preorder, 0, preorderSize - 1);
}
```