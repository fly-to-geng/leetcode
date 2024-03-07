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
    // 第一个结点作为跟结点，所有比它小的为做子树，所有比它大的为右子树
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