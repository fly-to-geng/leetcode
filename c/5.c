#define TRUE 1
#define FALSE 0
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int isH(char *s, int left, int right)
{
    while (left < right) {
        if (s[left] != s[right]) {
            return FALSE;
        }
        left += 1;
        right -= 1;
    }
    return TRUE;
}
char * longestPalindrome(char * s)
{
    int maxLen = 0;
    int start = 0;
    int end = 0;
    int i, j;
    char *ans;

    if (s == NULL) {
        return NULL;
    }

    if (strlen(s) == 0) {
        ans = (char*)malloc(sizeof(char));
        ans[0] = '\0';
        return ans;
    }

    for (i = 0; i < strlen(s) - 1; i++) {
        for (j = strlen(s) - 1; j > i; j--) {
            if (isH(s, i, j)) {
                if (j - i + 1 > maxLen) {
                    maxLen = j - i + 1;
                    start = i;
                    end = j;
                }
                /* 因为是从后向前扫描，如果找到回文，再向前就没有意义，这里直接结束本次循环，将i移动一位，继续寻找下一个可能的回文 */
                break;
            }
        }
    }

    ans = (char*)malloc(sizeof(char) * (end - start + 2));
    int ansEnd = 0;
    for (i = start; i <= end; i++) {
        ans[ansEnd++] = s[i];
    }
    ans[ansEnd] = '\0';
    return ans;
}