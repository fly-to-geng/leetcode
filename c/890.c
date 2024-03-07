#define N 26

int map[N];
int unique[N];
void init(int *array, int value)
{
    int i;
    for (i = 0; i < N; i++) {
        array[i] = value;
    }
}
int isMatch(char *str, char *pattern)
{
    int i;
    char a, b;
    int aa, bb;

    int n1 = strlen(str);
    int n2 = strlen(pattern);
    if (n1 != n2) {
        return false;
    }

    for (i = 0; i < n1; i++) {
        a = str[i];
        b = pattern[i];
        aa = a - 'a';
        bb = b - 'a';
        if (map[aa] == -1) {
            map[aa] = bb;
        } else if (map[aa] != bb) {
            return false;
        }
        if (unique[bb] == -1) {
            unique[bb] = aa;
        } else if (unique[bb] != aa) {
            return false;
        }
    }
    return true;    
}
char *copystr(char *str)
{
    int n = strlen(str);
    int i;
    char *newstr;
    newstr = (char*)malloc(sizeof(char) * (n + 1));
    for (i = 0; i < n; i++) {
        newstr[i] = str[i];
    }
    newstr[i] = '\0';
    return newstr;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findAndReplacePattern(char ** words, int wordsSize, char * pattern, int* returnSize){
    int i;
    char **ans;
    int ansEnd = 0;
    ans = (char**)malloc(sizeof(char*) * wordsSize);
    for (i = 0; i < wordsSize; i++) {
        init(map, -1);
        init(unique, -1);
        if (isMatch(words[i], pattern)) {
            ans[ansEnd++] = copystr(words[i]);
        }
    }
    *returnSize = ansEnd;
    return ans;
}