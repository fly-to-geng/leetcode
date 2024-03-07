int rangeBitwiseAnd(int m, int n){
    int diff = n - m;
    int ans = 0;
    long long base = 1;
    int i, j;
    if (diff == 0) {
        return m;
    }
    for (i = 0; i < 32; i++) {
        if (diff >= base) {
            m = m >> 1;
            n = n >> 1;
        } else {
            ans = m;
            for (j = m + 1; j <= n; j++) {
                ans = ans & j;
            }
            return ans << i;
        }
        base = base * 2;
    }
    return 0;
}