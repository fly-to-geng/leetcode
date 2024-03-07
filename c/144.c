#define N 1000 
typedef struct TreeNode Node;
typedef Node* NodePtr;
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *ansArray;
    int ansEnd = 0;
    NodePtr *stack;
    int stackEnd = 0;

    ansArray = (int*)malloc(sizeof(int) * N);
    stack = (NodePtr*)malloc(sizeof(NodePtr) * N);

    while (root != NULL || stackEnd > 0) {
        while (root != NULL) {
            ansArray[ansEnd++] = root->val;
            stack[stackEnd++] = root;
            root = root->left;
        }
        root = stack[--stackEnd];
        root = root->right;
    }
    *returnSize = ansEnd;

    /* 释放空间 */
    ansArray = realloc(ansArray,sizeof(int) * ansEnd);
    free(stack);
    return ansArray;
}