/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define N 100

// 返回叶子节点序列
void dfs(struct TreeNode *root, int *leaves, int *leavesEnd)
{
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        leaves[(*leavesEnd)++] = root->val;
    }
    if (root->left) {
        dfs(root->left, leaves, leavesEnd);
    }
    if (root->right) {
        dfs(root->right, leaves, leavesEnd);
    }
    return;
}
bool leafSimilar(struct TreeNode* root1, struct TreeNode* root2){
     int *l1; 
     int *l2;
     int l1End = 0;
     int l2End = 0;
     int i;

     l1 = (int*)malloc(sizeof(int) * N);
     l2 = (int*)malloc(sizeof(int) * N);
     dfs(root1, l1, &l1End);
     dfs(root2, l2, &l2End);
     if (l1End != l2End) {
         return false;
     }
     //printf("%d ", l1End);
     for (i = 0; i < l1End; i++) {
         if (l1[i] != l2[i]) {
             return false;
         }
     }
     return true;
}