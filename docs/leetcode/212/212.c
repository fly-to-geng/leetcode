#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHAR 26 // 字母种类，26个小写字母
#define MAX_WORD 500 // 一个单词的最大长度

int rows = 0;
int cols = 0;
char **gborad = NULL;
int **color = NULL;
char **ans = NULL;
int ansEnd = 0;

const int direct[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

typedef struct node{
    struct node* children[MAX_CHAR]; // 指向孩子们的指针数组
    char c; // 当前节点表示的字母
    bool isWord; // 记录单词结束标记
} Trie;

int** allocMatrix(int n, int m)
{
    int **matrix = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * m);
    }
    return matrix;
}
void fillMatrix(int **matrix, int n, int m, int val)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = val;
        }
    }
}
void freeMatrix(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
void initChildren(Trie **children, int size) {
    for (int i = 0; i < size; i++) {
        children[i] = NULL;
    }
}
char *deepCopy(char *string, int end)
{
    char *new_string = (char*)malloc(sizeof(char) * (end + 2));
    for (int i = 0; i < end; i++) {
        new_string[i] = string[i];
    }
    new_string[end] = '\0';
    return new_string;
}
bool notfind(char **words, int wordsSize, char *line, int end)
{
    line[end] = '\0';
    for (int i = 0; i < wordsSize; i++) {
        if (strcmp(words[i], line) == 0) {
            return false;
        }
    }
    return true;
}

Trie* trieCreate() {
    Trie *root = (Trie*)malloc(sizeof(Trie));
    root->c = ' ';
    root->isWord = false;
    initChildren(root->children, MAX_CHAR);
    return root;
}

void trieInsert(Trie* obj, char * word) {
    if (word == NULL) return;
    const int n = strlen(word);
    if (n == 0) return;

    Trie *curr = obj;
    for (int i = 0; i < n; i++) {
        int index = word[i] - 'a'; // 转换成索引
        if (curr->children[index] == NULL) {
            // 该字符还不存在，插入一个新的节点
            Trie *newNode = (Trie*)malloc(sizeof(Trie));
            newNode->c = word[i];
            newNode->isWord = (i == n - 1) ? true : false;
            initChildren(newNode->children, MAX_CHAR);
            curr->children[index] = newNode;
            curr = newNode;
        } else {
            // 如果存在，判断是否到了最后一个
            if (i == n - 1) {
                curr->children[index]->isWord = true;
            }
            curr = curr->children[index];
        }
    }
    return;
}

void trieFree(Trie* obj) {
    if (obj == NULL) return;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (obj->children[i] != NULL) {
            free(obj->children[i]);
        }
    }
    free(obj);
}

void dfs(int i, int j, Trie *root, char *line, int end)
{
    if (root->isWord) {
        line[end] = root->c;
        // 去重，此处可以使用哈希表加快速度
        if (notfind(ans, ansEnd, line, end + 1)) {
            ans[ansEnd++] = deepCopy(line, end + 1);
        }
    }
    color[i][j] = 1;
    for (int p = 0; p < MAX_CHAR; p++) {
        if (root->children[p] != NULL) {
            for (int k = 0; k < 4; k++) {
                int ni = i + direct[k][0];
                int nj = j + direct[k][1];
                if ( 0 <= ni && ni < rows && 0 <= nj && nj < cols && color[ni][nj] == 0) {
                    if (gborad[ni][nj] == root->children[p]->c) {
                        line[end] = root->c;
                        dfs(ni, nj, root->children[p], line, end + 1);
                    }
                }
            }
        }
    }
    color[i][j] = 0;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findWords(char** board, int boardSize, int* boardColSize, char ** words, int wordsSize, int* returnSize){
    
    *returnSize = 0;
    if (words == NULL || wordsSize <= 0) return NULL;
    if (board == NULL || boardSize <= 0) return NULL;
    if (boardColSize == NULL || boardColSize[0] == 0) return NULL;
    if (words[0] == 0) return NULL;

    rows = boardSize;
    cols = boardColSize[0];
    gborad = board;
    color = allocMatrix(rows, cols);
    ans = (char**)malloc(sizeof(char*) * wordsSize);
    ansEnd = 0;
    char *line = (char*)malloc(sizeof(char) * MAX_WORD);

    // 建立字典树
    Trie *root = trieCreate();
    for (int i = 0; i < wordsSize; i++) {
        trieInsert(root, words[i]);
    }

    // 对于以每个字母开头的单词，从矩阵中寻找到位置，从位置开始搜索
    for (int i = 0; i < MAX_CHAR; i++) {
        if (root->children[i] != NULL) {
            for (int p = 0; p < boardSize; p++) {
                for (int q = 0; q < boardColSize[p]; q++) {
                    if (board[p][q] == root->children[i]->c) {
                        fillMatrix(color, rows, cols, 0);
                        dfs(p, q, root->children[i], line, 0);
                    }
                }
            }
        }
    }

    trieFree(root);
    freeMatrix(color, rows, cols);
    free(line);

    rows = 0;
    cols = 0;
    gborad = NULL;
    color = NULL;

    *returnSize = ansEnd;
    return ans;   
}

int main()
{
    //[["a","b"],["a","a"]]
    //["aba","baa","bab","aaab","aaa","aaaa","aaba"]
    // 预期结果 ["aaa","aaab","aaba","aba","baa"]

    // ["a", "a"]
    // ["a"]
    // 预期结果：["a"]

    int boardSize = 2;
    int boardColsSize[] = {2,2};
    int wordSize = 7;
    char *words[7] = {"aba","baa","bab","aaab","aaa","aaaa","aaba"};
    char *board[2] = {"ab", "aa"};

    char **ans;
    int returnSize;
    ans = findWords(board, boardSize, boardColsSize, words, wordSize, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s, ", ans[i]);
    }
    return 0;
}

/*
    执行用时 :52 ms, 在所有 C 提交中击败了82.58%的用户
    内存消耗 :27 MB, 在所有 C 提交中击败了100.00%的用户
*/