#define N 1001
bool isMatch(char *s, char *pattern)
{
    int n = strlen(s);
    int m = strlen(pattern);
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (s[i] == pattern[j]) {
            i++;
            j++;
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            i++;
        } else {
            return false;
        }
    }
    if (j < m) {
        return false;
    }
    if (i < n) {
        while (i < n) {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                return false;
            }
            i++;
        }
    }
    return true;
}
bool* camelMatch(char ** queries, int queriesSize, char * pattern, int* returnSize){
    bool *ans;
    bool ansOne;
    int i;
    int ansEnd = 0;
    ans = (bool*)malloc(sizeof(bool) * N);
    for (i = 0; i< queriesSize; i++) {
        if (isMatch(queries[i], pattern)) {
            ans[ansEnd++] = true;
        } else {
            ans[ansEnd++] = false;
        }
    }
    (*returnSize) = ansEnd;
    return ans;
}