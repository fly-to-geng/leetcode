#define MAX_STRING 200

int max(int a, int b) 
{
    if (a > b) return a;
    return b;
}
char* deepCopy(char *s, int start, int end)
{
    char *ans = (char*)malloc(sizeof(char) * (end - start + 3));
    int ansEnd = 0;
    for (int i = start; i < end; i++) {
        ans[ansEnd++] = s[i];
    }
    ans[ansEnd] = '\0';
    return ans;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** printVertically(char * s, int* returnSize){
    char **strings = (char**)malloc(sizeof(char*) * MAX_STRING);
    int stringsEnd = 0;
    int start = 0;
    int end = 0;
    int n = strlen(s);
    while (start < n) {
        while(s[start] == ' ') start++;
        end = start;
        while (end < n && s[end] != ' ') end++;
        char *string = deepCopy(s, start, end);
        strings[stringsEnd++] = string;
        start = end;
    }
    
    int maxLen = 0;
    for (int i = 0; i < stringsEnd; i++) {
        maxLen = max(maxLen, strlen(strings[i]));
    }
    printf("%d," ,maxLen);
    
    char **ans = (char**)malloc(sizeof(char*) * maxLen);
    for (int i = 0; i < maxLen; i++) {
        ans[i] = (char*)malloc(sizeof(char) * stringsEnd);
        for (int j = 0; j < stringsEnd; j++) {
            ans[i][j] = ' ';
        }
    }
    
    // 按照垂直方向填充
    for (int i = 0; i < stringsEnd; i++) {
        for (int j = 0; j < strlen(strings[i]); j++) {
            ans[j][i] = strings[i][j];
        }
    }
    
    *returnSize = maxLen;
    return ans;
}

