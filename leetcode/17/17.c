#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NN 5000 // 最大答案数量
#define MM 200 // 最大digits长度

char *t9[] = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
char *d = NULL;
int size = 0;

char *deepCopy(char *str, int end)
{
    char *ans = (char*)malloc(sizeof(char) * (end + 1));
    int ansEnd = 0;
    for (int i = 0; i < end; i++) {
        ans[ansEnd++] = str[i];
    }
    ans[ansEnd] = '\0';
    return ans;
}
void dfs(int start, char *line, int lineEnd, char **ans, int *ansEnd)
{
    // 如果搜索到结尾，记录本次的搜索结果
    if (start == size) {
        ans[(*ansEnd)++] = deepCopy(line, lineEnd);
        return;
    }

    char *str = t9[ (d[start] - '0') - 2 ];
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        line[lineEnd] = str[i];
        dfs(start + 1, line, lineEnd + 1, ans, ansEnd);
    }
    return;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCombinations(char * digits, int* returnSize){
    if (digits == NULL || strlen(digits) == 0) {
        *returnSize = 0;
        return NULL;
    }

    char **ans = (char**)malloc(sizeof(char*) * NN);
    char *line = (char*)malloc(sizeof(char) * MM);
    int ansEnd = 0;

    d = digits;
    size = strlen(digits);
    dfs(0, line, 0, ans, &ansEnd);

    *returnSize = ansEnd;
    return ans;
}

int main()
{
    char digits[] = "234";
    int returnSize = 0;
    char **ans = letterCombinations(digits, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s, ", ans[i]);
    }
    return 0;
}