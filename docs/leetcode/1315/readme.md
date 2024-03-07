# [1315. 祖父节点值为偶数的节点和](https://leetcode-cn.com/problems/sum-of-nodes-with-even-valued-grandparent/)

## 题目描述

给你一棵二叉树，请你返回满足以下条件的所有节点的值之和：

该节点的祖父节点的值为偶数。（一个节点的祖父节点是指该节点的父节点的父节点。）
如果不存在祖父节点值为偶数的节点，那么返回 0 。

 

示例：

![](1473_ex1.png)

        输入：root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
        输出：18
        解释：图中红色节点的祖父节点的值为偶数，蓝色节点为这些红色节点的祖父节点。
         

提示：

        树中节点的数目在 1 到 10^4 之间。
        每个节点的值在 1 到 100 之间。

## 解题思路

```c
int computeSum(struct TreeNode* root)
{
    if (root == NULL) return 0;

    int ans = 0;
    if (root->left) {
        struct TreeNode* left = root->left;
        if (left->left) ans += left->left->val;
        if (left->right) ans += left->right->val;
    }
    if (root->right) {
        struct TreeNode* right = root->right;
        if (right->left) ans += right->left->val;
        if (right->right) ans += right->right->val;
    }
    return ans;
}

void dfs(struct TreeNode* root, int *ans)
{
    if (root->val % 2 == 0) {
        *ans += computeSum(root);
    }
    if (root->left) dfs(root->left, ans);
    if (root->right) dfs(root->right, ans);
    return; 
}

int sumEvenGrandparent(struct TreeNode* root){
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 0;

    int ans = 0;
    dfs(root, &ans);
    return ans;
}
```