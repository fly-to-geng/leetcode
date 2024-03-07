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