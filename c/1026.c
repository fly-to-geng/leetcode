/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define N 5000

int road[N];
int roadEnd = 0;
int ans = 0;

int abs2(int a, int b)
{
    if (a > b) {
        return a - b;
    } else {
        return b - a;
    }
}
// 计算新入栈的元素和栈内其他元素的差的绝对值
// 并更新 ans
void compute(int *road, int roadEnd)
{
    int i, diff;
    for (i = 0; i < roadEnd - 1; i++) {
        diff = abs2(road[i], road[roadEnd - 1]);
        if (diff > ans) {
            ans = diff;
        }
    }
    printf("%d ", ans);
}
void dfs(struct TreeNode* root, int *road, int *roadEnd)
{
    road[(*roadEnd)++] = root->val;
    compute(road, *roadEnd);
    if (root->left) {
        dfs(root->left, road, roadEnd);
    }
    if (root->right) {
        dfs(root->right, road, roadEnd);
    }
    (*roadEnd)--;
    return;
}
int maxAncestorDiff(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }
    roadEnd = 0;
    ans = 0;
    dfs(root, road, &roadEnd);
    return ans;
}