#define N 10001
int hashMap[N];
void init()
{
    int i;
    for (i = 0; i < N; i++) {
        hashMap[i] = 0;
    }
}
int subarraysDivByK(int* A, int ASize, int K){
    int *sums;
    int i;
    int ans = 0;

    sums = (int*)malloc(sizeof(int) * ASize);
    sums[0] = A[0];
    for (i = 1; i < ASize; i++) {
        sums[i] = sums[i - 1] + A[i];
    }
    init();
    for (i = 0; i < ASize; i++) {
        sums[i] = (sums[i] % K + K) % K;
        hashMap[sums[i]]++;
        if (sums[i] == 0) {
            ans++;
        }
    }
    for (i = 0; i < N; i++) {
        if (hashMap[i] != 0) {
            ans += hashMap[i] * (hashMap[i] - 1) / 2;
        }
    }
    return ans;
}