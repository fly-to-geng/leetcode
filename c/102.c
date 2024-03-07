#define MAX_ANS 1000 /* 结果应该不会超过1000个 */
#define MAX_IP 16 /* IP地址最多16个字符可以存储下 */
#define TRUE 1
#define FALSE 0


void dfs(char *s, int start, char *line, char **lines, int *linesEnd)
{
    if (start == strlen(s)) {
        lines[linesEnd++], line
    }
}
char ** restoreIpAddresses(char * s, int* returnSize){
    if (s == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int line[4];
    int lineEnd = 0; /* 4个整形存储一个IP地址 */

    char **lines;
    int linesEnd = 0; /* 字符串数组保存最终的结果 */

    lines = (char**)malloc(sizeof(cahr*) * MAX_ANS);
    for (i = 0; i < MAX_ANS; i++) {
        lines[i] = (char*)malloc(sizeof(char) * MAX_IP);
        memset(lines[i], 0, sizeof(cahr) * MAX_IP);
    }
    dfs(s, 0, line, &lineEnd, lines, &linesEnd);
    *returnSize = linesEnd;
    return lines;
}