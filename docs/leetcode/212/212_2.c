#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int rows = 0;
int cols = 0;
char **gborad = NULL;
int **color = NULL;

const int direct[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

char* deepCopy(char *string)
{
    const int n = strlen(string);
    char *ans = (char*)malloc(sizeof(char) * (n + 3));
    
    for (int i = 0; i < n; i++) {
        ans[i] = string[i];
    }
    ans[n] = '\0';
    return ans;
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

bool dfs(int i, int j, char *word, int index)
{
    if (index == strlen(word) - 1) {
        return true;
    }
    color[i][j] = 1;
    for (int k = 0; k < 4; k++) {
        int ni = i + direct[k][0];
        int nj = j + direct[k][1];
        if (0 <= ni && ni < rows && 0 <= nj && nj < cols) {
            if (gborad[ni][nj] == word[index + 1] && color[ni][nj] == 0) {
                bool result = dfs(ni, nj, word, index + 1);
                color[ni][nj] = 0;
                if (result) {
                    return true;
                }
            }
        }
    }
    color[i][j] = 0;
    return false;
}
bool find(char *word)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (gborad[i][j] == word[0]) {
                fillMatrix(color, rows, cols, 0);
                bool result = dfs(i, j, word, 0);
                if (result) {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findWords(char** board, int boardSize, int* boardColSize, 
                    char ** words, int wordsSize, int* returnSize)
{
    *returnSize = 0;
    if (words == NULL || wordsSize <= 0) return NULL;
    if (board == NULL || boardSize <= 0) return NULL;
    if (boardColSize == NULL || boardColSize[0] == 0) return NULL;
    if (words[0] == 0) return NULL;

    char **ans = (char**)malloc(sizeof(char*) * wordsSize);
    int ansEnd = 0;
    int **cc = (int **)malloc(sizeof(int*) * boardSize);
    for (int i = 0; i < boardSize; i++) {
        cc[i] = (int*)malloc(sizeof(int) * boardColSize[i]);
    }

    // 设置全局变量， 尽量少传参数
    rows = boardSize;
    cols = boardColSize[0];
    gborad = board;
    color = cc;

    for (int i = 0; i < wordsSize; i++) {
        bool result = find(words[i]);
        if (result) {
            ans[ansEnd++] = deepCopy(words[i]);
        }
    }

    freeMatrix(cc, rows, cols);

    rows = 0;
    cols = 0;
    gborad = NULL;
    color = NULL;

    *returnSize = ansEnd;
    return ans;
}
int main()
{
    int boardSize = 4;
    int boardColsSize[] = {4,4,4,4};
    int wordSize = 4;
    char *words[4] = {"oath","pea","eat","rain"};
    char *board[4] = {"oaan","etae","ihkr","iflv"};

    char **ans;
    int returnSize;
    ans = findWords(board, boardSize, boardColsSize, words, wordSize, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s, ", ans[i]);
    }
    return 0;
}

/*
执行用时 :1240 ms, 在所有 C 提交中击败了13.87%的用户
内存消耗 :8.3 MB, 在所有 C 提交中击败了100.00%的用户
*/