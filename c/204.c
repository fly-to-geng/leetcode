/* 是质数返回1，不是返回0 */
int isPrime(int a)
{
    int i;
    for (i = 2; i * i <= a; i++) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;
}
int countPrimes(int n){
    int ans = 0;
    int i;

    /* 1不是质数 */
    for (i = 2; i < n; i++) {
        ans += isPrime(i);
    }
    return ans;
}