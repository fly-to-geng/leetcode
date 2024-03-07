int f(char *s)
{
    int i;
    int n = strlen(s);
    int count = 1;
    char c = s[0];
    for (i = 1; i < n; i++) {
        if (s[i] < c) {
            c = s[i];
            count = 1;
        } else if (c == s[i]) {
            count++;
        }
    }
    return count;
}
int* numSmallerByFrequency(char ** queries, int queriesSize, char ** words, int wordsSize, int* returnSize){
    int i, j;
    int count;
    int n;
    int *wordCount;
    int ans;
    int *ansArray;
    wordCount = (int*)malloc(sizeof(int) * wordsSize);
    ansArray = (int*)malloc(sizeof(int) * queriesSize);
    for (i = 0; i < wordsSize; i++) {
        wordCount[i] = f(words[i]);
    }
    for (i = 0; i < queriesSize; i++) {
        count = f(queries[i]);
        ans = 0;
        for (j = 0; j < wordsSize; j++) {
            if (count < wordCount[j]) {
                ans++;
            }
        }
        ansArray[i] = ans;
    }
    (*returnSize) = queriesSize;
    free(wordCount);
    return ansArray;
}