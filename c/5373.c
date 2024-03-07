#define MAXN 50000

int findMinFibonacciNumbers(int k){
    int *arr = (int*)malloc(sizeof(int) * MAXN);
    arr[0] = 1;
    arr[1] = 1;
    int i = 0;
    while (i < MAXN && arr[i] + arr[i + 1] < k) {
        arr[i+2] = arr[i] + arr[i+1];
        i++;
    }
    int end = i + 1;
    int ans = 0;
    while (k != 0) {
        while (end >= 0 && arr[end] > k) {
            end--;
        }
        if (k >= 0) {
            k = k - arr[end];
            ans += 1;
        }
    }
    if (k == 0) {
        return ans;
    } else {
        return -1;
    }
}

