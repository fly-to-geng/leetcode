#define N 10002

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void middle(struct TreeNode* root, int *arr, int *arrEnd)
{
    if (root == NULL) return;
    if (root->left) {
        middle(root->left, arr, arrEnd);
    }
    arr[(*arrEnd)++] = root->val;
    if (root->right) {
        middle(root->right, arr, arrEnd);
    }
    return;
}

struct TreeNode* balanceDFS(int *arr, int start, int end)
{
    if (start > end) return NULL;

    if (start == end) {
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->val = arr[start];
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    int mid = (end + start) / 2;
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = arr[mid];
    newNode->left = balanceDFS(arr, start, mid - 1);
    newNode->right = balanceDFS(arr, mid + 1, end);
    return newNode;
}

struct TreeNode* balanceBST(struct TreeNode* root){
    if (root == NULL) return root;

    int *array = (int*)malloc(sizeof(int) * N);
    int arrayEnd = 0;

    middle(root, array, &arrayEnd); // 中序遍历得到排序好的数组
    for (int i = 0; i < arrayEnd; i++) {
        printf("%d ", array[i]);
    }

    int mid = (arrayEnd - 1) / 2;
    root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = array[mid];
    root->left = balanceDFS(array, 0, mid - 1);
    root->right = balanceDFS(array, mid + 1, arrayEnd - 1);

    free(array);

    return root;
}