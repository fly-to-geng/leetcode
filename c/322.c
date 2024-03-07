#define MIN(a,b) ((a) > (b) ? (b) : (a))

int compare(const void *p, const void *q)
{
    int a = *(int *)p;
    int b = *(int *)q;
    return a - b;
}
int coinChange(int* coins, int coinsSize, int amount){
    int **dp;
    int i, j;
    int ans1, ans2, ans;

    qsort(coins, coinsSize, sizeof(int), compare);

    dp = (int**)malloc(sizeof(int*) * coinsSize);
    for (i = 0; i < coinsSize; i++) {
        dp[i] = (int*)malloc(sizeof(int) * (amount + 1));
        memset(dp[i], 0, sizeof(int) * (amount + 1));
    }

    // 填充第一行，只使用第一个硬币
    for (j = 0; j <= amount; j++) {
        if (j % coins[0] == 0) {
            dp[0][j] = j / coins[0];
        }
    }

    for (i = 1; i < coinsSize; i++) {
        for (j = 1; j <= amount; j++) {
            // 无法使用第j个硬币，因为它本身就比目标大
            if (coins[i] > j) {
                dp[i][j] = dp[i-1][j];
            } else {
                ans1 = dp[i-1][j]; // 使用前i-1个硬币组成j
                ans2 = dp[i][j - coins[i]] + 1; // 使用前i个组成j-coins[j] + 一个当前硬币
                dp[i][j] = MIN(ans1, ans2);
            }
        }
    }

    for (i = 0; i < coinsSize; i++) {
        for (j = 0; j <= amount; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    if (amount == 0) {
        ans = 0;
    } else if (dp[coinsSize-1][amount] == 0) {
       ans = -1;
    } else {
        ans = dp[coinsSize-1][amount];
    }

    // 释放申请的空间
    for (i = 0; i < coinsSize; i++) {
        free(dp[i]);
    }
    free(dp);

    return ans;
}