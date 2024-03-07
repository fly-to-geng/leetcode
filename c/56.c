#define MAX_ANS_SIZE 1000
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int compare(const void *p, const void *q)
{
    int *a = *(int**)p;
    int *b = *(int**)q;
    return a[0] - b[0];
}
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes)
{
    int *columnsSize = (int*)malloc(sizeof(int) * MAX_ANS_SIZE);
    if (intervals == NULL || intervalsColSize == NULL || intervalsSize <= 0) {
        *returnColumnSizes = columnsSize;
        *returnSize = 0;
        return NULL;
    }

    qsort(intervals, intervalsSize, sizeof(int) * 2, compare);

    // 用label标记区间是否留下来
    int start = 0;
    int *label = (int*)malloc(sizeof(int) * intervalsSize);
    for (int i = 0; i < intervalsSize; i++) {
        label[i] = 1;
    }

    // 比较相邻的区间，如果有重叠，就合并区间
    while (start < intervalsSize - 1) {
        if (intervals[start][1] >= intervals[start + 1][0]) {
            intervals[start + 1][0] = intervals[start][0];
            intervals[start + 1][1] = MAX(intervals[start][1], intervals[start + 1][1]);
            label[start] = 0;
        }
        start++;
    }

    // 统计合并之后剩下多少区间
    int count = 0;
    for (int i = 0; i < intervalsSize; i++) {
        if (label[i] == 1) {
            count++;
        }
    }

    // 组装最后的结果
    int **ans = (int**)malloc(sizeof(int*) * count);
    int ansEnd = 0;
    *returnSize = count;
    for (int i = 0; i < count; i++) {
        ans[i] = (int*)malloc(sizeof(int) * 2);
    }
    for (int i = 0; i < intervalsSize; i++) {
        if (label[i] == 1) {
            ans[ansEnd][0] = intervals[i][0];
            ans[ansEnd][1] = intervals[i][1];
            ansEnd++;
        }
    }
    for (int i = 0; i < count; i++) {
        columnsSize[i] = 2;
    }
    *returnColumnSizes = columnsSize;

    // 释放无用的空间
    free(label);

    return ans;
}