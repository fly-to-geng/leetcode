#define MAX_ANS 1000

char ***ans;
int ansEnd;
int *colsSize = NULL;
int colsEnd = 0;
char *sg;
int size;

// 释放字符串数组所占用的空间
void freeStrings(char **strings, int size)
{
    for (int i = 0; i < size; i++) {
        free(strings[i]);
    }
    free(strings);
}

// 深度拷贝 string[start : end]
char *strDeepCopy(char *string, int start, int end)
{
    char *newString = (char*)malloc(sizeof(char) * (end - start + 2));
    int newStringEnd = 0;

    for (int i = start; i <= end; i++) {
        newString[newStringEnd++] = string[i];
    }
    newString[newStringEnd] = '\0';

    return newString;
}

// 深度拷贝一个字符串数组
char **deepCopy(char **strings, int size)
{
    char **ans = (char**)malloc(sizeof(char*) * size);
    for (int i = 0; i < size; i++) {
        ans[i] = strDeepCopy(strings[i], 0, strlen(strings[i]) - 1);
    }
    return ans;
}

int isHuiWen(char *string, int start, int end)
{
    while(start <= end) {
        if (sg[start] != string[end]) {
            return false;
        }
        start++, end--;
    }
    return true;
}

void dfs(int start, int end, char **line, int *lineEnd)
{
    if (end == size) {
        if (start == end) {
            ans[ansEnd++] = deepCopy(line, *lineEnd);
            colsSize[colsEnd++] = *lineEnd;
        }
        return;
    }

    // 如果[start, end] 是回文，从这里切割一下
    if (isHuiWen(sg, start, end)) {
        line[(*lineEnd)++] = strDeepCopy(sg, start, end);
        dfs(end+1, end+1, line, lineEnd);
        (*lineEnd)--;
    }

    // 不切割，继续向下搜索
    dfs(start, end+1, line, lineEnd);
    return;
}

char *** partition(char * s, int* returnSize, int** returnColumnSizes)
{
    ans = NULL;
    ansEnd = 0;
    colsSize = NULL;
    colsEnd = 0;
    sg = NULL;

    if (s == NULL || strlen(s) == 0) {
        *returnSize = 0;
        *returnColumnSizes = colsSize;
        return ans;
    }

    size = strlen(s);
    char **line = (char**)malloc(sizeof(char*) * size);
    int lineEnd = 0;
    ans = (char***)malloc(sizeof(char**) * MAX_ANS);
    colsSize = (int*)malloc(sizeof(int) * MAX_ANS);

    sg = s;
    dfs(0, 0, line, &lineEnd);

    *returnSize = ansEnd;
    *returnColumnSizes = colsSize;

    freeStrings(line, lineEnd);

    return ans;
}