#define N 1000 
typedef struct TreeNode Node;
typedef Node* NodePtr;
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* postorderTraversal(struct TreeNode* root, int* returnSize)
{
    int *ansArray;
    int ansEnd = 0;
    NodePtr *stack;
    int stackEnd = 0;
    struct TreeNode *lastVisited = root;

    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    ansArray = (int*)malloc(sizeof(int) * N);
    stack = (NodePtr*)malloc(sizeof(NodePtr) * N);

    stack[stackEnd++] = root;
    while (stackEnd > 0) {
        root = stack[stackEnd-1];
        if (root->left == NULL && root->right == NULL ||
            root->right == NULL && lastVisited == root->left ||
            lastVisited == root->right) {
                ansArray[ansEnd++] = root->val;
                lastVisited = root;
                stackEnd--;
        } else {
            if (root->right != NULL) {
                stack[stackEnd++] = root->right;
            }
            if (root->left != NULL) {
                stack[stackEnd++] = root->left;
            }
        }
    }
    *returnSize = ansEnd;

    /* 释放空间 */
    ansArray = realloc(ansArray,sizeof(int) * ansEnd);
    free(stack);
    return ansArray;
}