void dfs(struct TreeNode *root, int num, int *sum)
{
    num = num * 10 + root->val;
    if (root->left == NULL && root->right == NULL) {
        *sum = *sum + num;
    }
    if (root->left) {
        dfs(root->left, num, sum);
    }
    if (root->right) {
        dfs(root->right, num, sum);
    }
    return;
}
int sumNumbers(struct TreeNode* root){
    int sum = 0;
    int num = 0;
    if (root == NULL) return sum;
    dfs(root, num, &sum);
    return sum; 
}