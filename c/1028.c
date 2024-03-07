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