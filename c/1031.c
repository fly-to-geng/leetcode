#define MAX(a, b) ((a) > (b)) ? (a) : (b)
int getMSum(int *A, int *aSum, int ASize, int i, int L, int M)
{
    int lefts = 0;
    int lefte = i - 1;
    int rights = i + L;
    int righte = ASize - 1;
    int maxv = -1;
    int j, tmp;

    if (lefte - lefts + 1 >= M) {
        for (j = lefts; j <= lefte - M + 1; j++) {
            tmp = aSum[j + M] - aSum[j];
            maxv = MAX(maxv, tmp);
        }
    }

    if (righte - rights + 1 >= M) {
        for (j = rights; j <= righte - M + 1; j++) {
            tmp = aSum[j + M] - aSum[j];
            maxv = MAX(maxv, tmp);
        }
    }
    return maxv;
}
int maxSumTwoNoOverlap(int* A, int ASize, int L, int M){
    int *aSum;
    int lSum = 0;
    int mSum = 0;
    int sum = 0;
    int ans = 0;
    int i, j;

    if (A == NULL || ASize == 0) {
        return 0;
    }

    /* 求前缀和 */
    aSum = (int*)malloc(sizeof(int) * (ASize + 1));
    aSum[0] = 0;
    for (i = 0; i < ASize; i++) {
        aSum[i + 1] = aSum[i] + A[i];
    }

    /* 确定L，寻找可能的最大的M */
    for (i = 0; i <= ASize - L; i++) {
        lSum = aSum[i + L] - aSum[i];
        mSum = getMSum(A, aSum, ASize, i, L, M);
        sum = lSum + mSum;
        ans = MAX(ans, sum);
    }
    return ans;
}