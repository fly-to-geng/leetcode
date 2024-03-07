#define MAX_ANS 1000
#define true 1
#define false 0

char **wordsGlobal = NULL;
int wordsSizeGlobal = 0;
int *wordsMap = NULL; // 保存words中的单词出现的次数
int wordsMapSize = 0; // 记录wordsMap中存有多少个单词

char *substr(char *s, int start, int len)
{
    int end = 0;
    char *newString = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = start; i < start + len; i++) {
        newString[end++] = s[i];
    }
    newString[end] = '\0';
    return newString;
}

// indexOf 返回word 在 words 中的索引，没有返回-1
int indexOf(char *word)
{
    for (int i = 0; i < wordsSizeGlobal; i++) {
        if (strcmp(wordsGlobal[i], word) == 0 && wordsMap[i] == 1) {
            return i;
        }
    }

    return -1;
}

// 是否是一个拼接
// 从 start 开始，每m个字符是一个单词，一共有k个单词
int isSatisfied(char *s, int start, int m, int k)
{
    wordsMapSize = wordsSizeGlobal;
    for (int i = 0; i < wordsSizeGlobal; i++) {
        wordsMap[i] = 1;
    }

    for (int i = 0; i < k; i++) {
        char *word = substr(s, start + m * i, m);
        int index = indexOf(word);
        if (index != -1) {
            wordsMap[index] -= 1;
            wordsMapSize--;
        } else {
            return false;
        }
    }

    if (wordsMapSize == 0) {
        return true;
    } else {
        return false;
    }
}

int* findSubstring(char * s, char ** words, int wordsSize, int* returnSize)
{
    if (s == NULL || words == NULL || wordsSize <= 0) {
        *returnSize = 0;
        return NULL;
    }

    int slen = strlen(s);
    int wlen = strlen(words[0]);
    if (slen < wlen * wordsSize) {
        *returnSize = 0;
        return NULL;
    }

    int *ans = (int*)malloc(sizeof(int) * MAX_ANS);
    int ansEnd = 0;
    int result;
    int m = strlen(words[0]);
    int n = m * wordsSize;

    wordsGlobal = words;
    wordsSizeGlobal = wordsSize;

    wordsMap = (int*)malloc(sizeof(int) * wordsSize);
    wordsMapSize = wordsSize;

    for (int i = 0; i <= strlen(s) - n; i++) {
        result = isSatisfied(s, i, m, wordsSize);
        if (result) {
            ans[ansEnd++] = i;
        }
    }

    *returnSize = ansEnd;
    return ans;
}