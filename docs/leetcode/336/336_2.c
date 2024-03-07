char tmp[1000];

bool isHuiwen(char *word1, char *word2)
{
    int n1 = strlen(word1);
    int n2 = strlen(word2);
    int end = 0;
    for (int i = 0; i < n1; i++) tmp[end++] = word1[i];
    for (int i = 0; i < n2; i++) tmp[end++] = word2[i];
    int left = 0, right = end - 1;
    while (left < right) {
        if (tmp[left] != tmp[right]) {
            return false;
        }
        left++, right--;
    }
    return true;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** palindromePairs(char ** words, int wordsSize, int* returnSize, int** returnColumnSizes){
    int *cols = (int*)malloc(sizeof(int) * wordsSize * wordsSize);
    int **ans = (int**)malloc(sizeof(int*) * wordsSize * wordsSize);
    int ansEnd = 0;
    for (int i = 0; i < wordsSize * wordsSize; i++) ans[i] = (int*)malloc(sizeof(int) * 2);
    for (int i = 0; i < wordsSize * wordsSize; i++) cols[i] = 2;

    for (int i = 0; i < wordsSize; i++) {
        for (int j = 0; j < wordsSize; j++) {
            if (i != j && isHuiwen(words[i], words[j])) {
                ans[ansEnd][0] = i;
                ans[ansEnd][1] = j;
                ansEnd++;
            }
        }
    }

    *returnSize = ansEnd;
    *returnColumnSizes = cols;
    return ans;
}

/*
80 / 134 个通过测试用例
*/