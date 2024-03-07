#define MAX_ONE_LINE_SIZE 1000
#define MAX_ANS_SIZE 1000

const int *candidateGlobal = NULL; // 指向数组
int nGlobal = 0; 
int **lines; // 指向最终的结果
int linesEnd = 0;
int *columnsSize; // 指向一个数组，表示每行元素的个数
int columnsSizeEnd = 0;

// 实现排序比较函数
int compare(const void *p, const void *q)
{
    int a = *(int*)p;
    int b = *(int*)q;
    return a - b;
}

// 深度拷贝一个整数数组，在函数中开辟空间返回
int *deepCopy(int *array, int size)
{
    int *newArray = (int*)malloc(sizeof(int) * size);
    memcpy(newArray, array, sizeof(int) * size);
    return newArray;
}

// 从第i个数字开始深度优先搜索，一趟结果放在line中，最终结果放在lines中
void dfs(int i, int target, int *line, int *lineEnd)
{
    if (target == 0) {
        lines[linesEnd++] = deepCopy(line, *lineEnd);
        columnsSize[columnsSizeEnd++] = *lineEnd;
        return;
    }

    for (int j = i; j < nGlobal; j++) {
        if (candidateGlobal[j] > target) {
            break;
        }
        line[(*lineEnd)++] = candidateGlobal[j];
        dfs(j, target - candidateGlobal[j], line, lineEnd);
        (*lineEnd)--;
    }
}



int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes)
{
    // 存储每一趟扫描的结果
    int *line = (int*)malloc(sizeof(int) * MAX_ONE_LINE_SIZE);
    int lineEnd = 0;

    // 存储最终的结果
    lines = (int**)malloc(sizeof(int*) * MAX_ANS_SIZE);
    linesEnd = 0;

    // 存储每行的大小
    columnsSize = (int*)malloc(sizeof(int) * MAX_ANS_SIZE);
    columnsSizeEnd = 0;

    candidateGlobal = candidates;
    nGlobal = candidatesSize;

    qsort(candidateGlobal, nGlobal, sizeof(int), compare);

    dfs(0, target, line, &lineEnd);

    *returnSize = linesEnd;
    *returnColumnSizes = columnsSize;

    // line 用来存储每趟扫描的结果，是临时变量，不使用应该释放
    free(line);

    // 其他申请的空间都是最后答案的一部分，无须释放
    return lines;
}