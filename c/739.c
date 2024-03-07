/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* T, int TSize, int* returnSize){
    int *ans;
    int i, j;

    ans = (int*)malloc(sizeof(int) * TSize);
    memset(ans, 0, sizeof(int) * TSize);
    for (i = TSize - 2; i >= 0; i--) {
        if (T[i] < T[i + 1]) {
            ans[i] = 1;
        } else {
            j = i + 1;
            while (j < TSize && T[i] >= T[j]) {
                if (ans[j] == 0) {
                    break;
                }
                j = j + ans[j];
            }
            if (j < TSize && j > i && T[j] > T[i]) {
                ans[i] = j - i;
            }
        }
    }
    *returnSize = TSize;
    return ans;
}