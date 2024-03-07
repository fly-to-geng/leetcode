#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uthash.h>

#define MAXN 10000

struct HashMap{
    char text[MAXN]; // 文件内容
    char *paths[MAXN]; // 文件绝对路径
    int pathsNum; // 绝对路径的个数
    UT_hash_handle hh;
};

typedef struct HashMap FilePath;

char *substr(char *string, int start, int end)
{
    char *ans = (char*)malloc(sizeof(char) * (end - start + 2));
    int ansEnd = 0;
    for (int i = start; i <= end; i++) {
        ans[ansEnd++] = string[i];
    }
    ans[ansEnd] = '\0';
    return ans;
}
char *addpath(char *str1, char *str2)
{
    int n1 = strlen(str1);
    int n2 = strlen(str2);
    char *ans = (char*)malloc(sizeof(char) * (n1 + n2 + 4));
    int ansEnd = 0;
    for (int i = 0; i < n1; i++) {
        ans[ansEnd++] = str1[i];
    }
    ans[ansEnd++] = '/';
    for (int i = 0; i < n2; i++) {
        ans[ansEnd++] = str2[i];
    }
    ans[ansEnd] = '\0';
    return ans;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** findDuplicate(char ** paths, int pathsSize, int* returnSize, int** returnColumnSizes){
    char ***ans = (char***)malloc(sizeof(char**) * MAXN);
    int ansEnd = 0;
    int *colsSize = (int*)malloc(sizeof(int) * MAXN);
    int colsEnd = 0;
    FilePath *map = NULL;
    FilePath *curr = NULL;

    for (int i = 0; i < pathsSize; i++) {
        char *originPathStr = paths[i];
        int n = strlen(originPathStr);
        int *space = (int*)malloc(sizeof(int) * n);
        int spaceEnd = 0;
        for (int j = 0; j < n; j++) {
            if (originPathStr[j] == ' ') {
                space[spaceEnd++] = j;
            }
        }
        char *path1 = substr(originPathStr, 0, space[0] - 1);
        char *path2 = NULL;
        for (int j = 0; j < spaceEnd; j++) {
            if (j == spaceEnd - 1) {
                path2 = substr(originPathStr, space[j] + 1, n - 1);
            } else {
                path2 = substr(originPathStr, space[j] + 1, space[j + 1] - 1);
            }
            int start = -1;
            int end = -1;
            for (int k = 0; k < strlen(path2); k++) {
                if (path2[k] == '(') {
                    start = k;
                }
                if (path2[k] == ')') {
                    end = k;
                }
            }
            char *filename = substr(path2, 0, start - 1);
            char *filecontent = substr(path2, start + 1, end - 1);
            HASH_FIND_STR(map, filecontent, curr);
            if (curr == NULL) {
                curr = (FilePath*)malloc(sizeof(FilePath));
                strcpy(curr->text, filecontent); curr->text[strlen(filecontent)] = '\0';
                curr->paths[0] = addpath(path1, filename);
                curr->pathsNum = 1;
                HASH_ADD_STR(map, text, curr);
            } else {
                curr->paths[curr->pathsNum] = addpath(path1, filename);
                curr->pathsNum += 1;
            }
            free(filename);
            free(filecontent);
            free(path2);
        }
        free(space);
        free(path1);
    }

    for (curr = map; curr != NULL; curr = curr->hh.next) {
        if (curr->pathsNum > 1) {
            ans[ansEnd++] = curr->paths;
            colsSize[colsEnd++] = curr->pathsNum;
        }
    }

    *returnSize = ansEnd;
    *returnColumnSizes = colsSize;
    return ans;
}