#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXANS 3000
#define MAXLINE 1000

int *can = NULL;
int n = 0;
int *cols = NULL;
int colsEnd = 0;

int compare(const void *a, const void *b)
{
    int n1 = *(int*)a;
    int n2 = *(int*)b;
    return n1 - n2;
}
int *deepCopy(int *arr, int n)
{
    int *ans = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        ans[i] = arr[i];
    }
    return ans;
}
void dfs(int start, int target, int *line, int lineEnd, int **ans, int *ansEnd)
{
    if (target == 0) {
        ans[(*ansEnd)++] = deepCopy(line, lineEnd);
        cols[colsEnd++] = lineEnd;
        return;
    }
    for (int i = start; i < n; i++) {
        if (can[i] > target) {
            break;
        }
        line[lineEnd++] = can[i];
        dfs(i, target - can[i], line, lineEnd, ans, ansEnd);
        lineEnd--;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){
    int *colsSize = (int*)malloc(sizeof(int) * MAXANS);
    int colsSizeEnd = 0;
    int **ans = (int**)malloc(sizeof(int*) * MAXANS);
    int ansEnd = 0;

    if (candidates == 0 || candidatesSize == 0 || target <= 0) {
        *returnSize = 0;
        *returnColumnSizes = colsSize;
        return NULL;
    }

    can = candidates;
    n = candidatesSize;
    cols = colsSize;
    colsEnd = colsSizeEnd;
    int *line = (int*)malloc(sizeof(int) * MAXLINE);
    int lineEnd = 0;

    qsort(can, n, sizeof(int), compare);
    dfs(0, target, line, lineEnd, ans, &ansEnd);

    *returnSize = ansEnd;
    *returnColumnSizes = colsSize;
    free(line);
    return ans;
}

int main()
{
    return 0;
}