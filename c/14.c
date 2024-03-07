#define TRUE 1
#define FALSE 0

int notSame(char **strs, int strsSize, int index)
{
    int i;
    for (i = 0; i < strsSize; i++) {
        if (index >= strlen(strs[i])) {
            return TRUE;
        }
        if (i != strsSize - 1 && strs[i][index] != strs[i + 1][index]) {
            return TRUE;
        }
    }
    return FALSE;
}
char * longestCommonPrefix(char ** strs, int strsSize){
    int index = 0;
    char *ans;
    int ansEnd = 0;
    int i;
    int maxlen;

    if (strs == NULL || strsSize == 0) {
        ans = (char*)malloc(sizeof(char));
        ans[0] = '\0';
        return ans;
    }

    /* 获取字符串中最长的那一个 */
    maxlen = 0;
    for (i = 0; i < strsSize; i++) {
        if (strlen(strs[i]) > maxlen) {
            maxlen = strlen(strs[i]);
        }
    }
    for (i = 0; i < maxlen; i++) {
        if (notSame(strs, strsSize, index)) {
            break;
        }
        index += 1;
    }
    ans = (char*)malloc(sizeof(char) * (index + 1));
    for (i = 0; i < index; i++) {
        ans[ansEnd++] = strs[0][i];
    }
    ans[ansEnd] = '\0';
    return ans;
}