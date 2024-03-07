#define MAX_ONE_LINE 1000
#define MAX_ANS_SIZE 1000

int **lines;
int linesEnd = 0;
int *columnsSize;
int columnsSizeEnd = 0;
int *arrayGlobal;
int n;

int compare(const void *p, const void *q)
{
    int a = *(int *)p;
    int b = *(int *)q;
    return a - b;
}

int *deepCopy(int *array, int size)
{
    int *newArray = (int*)malloc(sizeof(int) * size);
    memcpy(newArray, array, sizeof(int) * size);
    return newArray;
}

void dfs(int i, int target, int *line, int *lineEnd)
{
    // 如果得到结果，存储
    if (target == 0) {
        lines[linesEnd++] = deepCopy(line, *lineEnd);
        columnsSize[columnsSizeEnd++] = *lineEnd;
        return;
    }

    for (int j = i + 1; j < n; j++) {
        if (j > i + 1 && arrayGlobal[j] == arrayGlobal[j-1]) {
            continue;
        }
        if (arrayGlobal[j] > target) {
            break;
        }

        line[(*lineEnd)++] = arrayGlobal[j];
        dfs(j, target - arrayGlobal[j], line, lineEnd);
        (*lineEnd)--;
    }

    return;
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes)
{
    // 存储一趟搜索结果
    int *line = (int*)malloc(sizeof(int) * MAX_ONE_LINE);
    int lineEnd = 0;

    // 存储最终搜索结果
    lines = (int**)malloc(sizeof(int*) * MAX_ANS_SIZE);
    linesEnd = 0;

    // 存储每一行的大小
    columnsSize = (int*)malloc(sizeof(int*) * MAX_ANS_SIZE);
    columnsSizeEnd = 0;

    arrayGlobal = candidates;
    n = candidatesSize;
    qsort(arrayGlobal, n, sizeof(int), compare);

    // 以每一个为起点深度搜索， 跳过重复的开始节点
    for (int i = 0; i < n; i++) {
        if (i > 0 && arrayGlobal[i] == arrayGlobal[i-1]) {
            continue;
        }
        line[lineEnd++] = arrayGlobal[i];
        dfs(i, target - arrayGlobal[i], line, &lineEnd);
        lineEnd--;
    }

    *returnSize = linesEnd;
    *returnColumnSizes = columnsSize;

    free(line);

    return lines;
}