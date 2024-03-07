# [1028. 从先序遍历还原二叉树](https://leetcode-cn.com/problems/recover-a-tree-from-preorder-traversal/)

## 题目描述

我们从二叉树的根节点 root 开始进行深度优先搜索。

在遍历中的每个节点处，我们输出 D 条短划线（其中 D 是该节点的深度），然后输出该节点的值。（如果节点的深度为 D，则其直接子节点的深度为 D + 1。根节点的深度为 0）。

如果节点只有一个子节点，那么保证该子节点为左子节点。

给出遍历输出 S，还原树并返回其根节点 root。

 

示例 1：

![](tree1.png)

        输入："1-2--3--4-5--6--7"
        输出：[1,2,5,3,4,6,7]

示例 2：

![](tree2.png)

        输入："1-2--3---4-5--6---7"
        输出：[1,2,5,3,null,6,null,4,null,7]

示例 3：

![](tree3.png)

        输入："1-401--349---90--88"
        输出：[1,401,null,349,88,90]

提示：

        原始树中的节点数介于 1 和 1000 之间。
        每个节点的值介于 1 和 10 ^ 9 之间。

## 解题思路

```c++
#define N 1002

struct TreeNode *nodeStack[N];
int nodeStackEnd = 0;
int levelStack[N];
int levelStackEnd = 0;

// 返回解析出来的 number, level, 和下一次开始的位置
int parse(char *S, int i, int *level, int *next)
{
    int l = 0;
    int num = 0;
    int j;
    int n = strlen(S);
    j = i;
    while (j < n && S[j] == '-') {
        l++;
        j++;
    }
    while (j < n && S[j] >= '0' && S[j] <= '9') {
        num = num * 10 + S[j] - '0';
        j++;
    }
    (*next) = j;
    (*level) = l;
    return num;
}


struct TreeNode* recoverFromPreorder(char * S){
    int i = 0;
    int j;
    int d; // 短横线的数量
    int next;
    int num;
    struct TreeNode *root;
    struct TreeNode *newNode;
    struct TreeNode *curNode;
    int number;
    int level = 0;
    int curLevel = 0;
    int n = strlen(S);
    if (S == NULL || n == 0) {
        return NULL;
    }
    j = 0;
    num = 0;
    while (j < n && S[j] >= '0' && S[j] <= '9') {
        num = num * 10 + S[j] - '0';
        j++;
    }
    root = (struct TreeNode*)malloc(sizeof(struct TreeNode)); 
    root->left = NULL;
    root->right = NULL;
    root->val = num;
    if (n == j) {
       return root;
    }
    nodeStack[nodeStackEnd++] = root;
    levelStack[levelStackEnd++] = 0;
    curLevel = 0;
    for (i = j; i < strlen(S); i++) {
        level = 0;
        next = 0;
        number = parse(S, i, &level, &next);
        if (level == curLevel + 1) {
            // 说明是栈顶元素的左子树
            newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            newNode->val = number;
            newNode->left = NULL;
            newNode->right = NULL;
            nodeStack[nodeStackEnd - 1]->left = newNode;
            nodeStack[nodeStackEnd++] = newNode;
            levelStack[levelStackEnd++] = level;
        } else if (level < curLevel + 1) {
            while (levelStackEnd > 0 && levelStack[levelStackEnd - 1] >= level) {
                levelStackEnd--;
                nodeStackEnd--;
            }
            curNode = nodeStack[nodeStackEnd - 1];
            newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->val = number;
            curNode->right = newNode;
            nodeStack[nodeStackEnd++] = newNode;
            levelStack[levelStackEnd++] = level;
        } else {
            
        }
        i = next - 1;
        curLevel = level;
    }
    return root;
}
```