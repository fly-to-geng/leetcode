#define N 300
int r[N];

int uniquePaths(int m, int n){
    int i;
    int j;
    for (i = 0; i < n; i++) {
        r[i] = 1;
    }
    for (i = 1; i < m; i++) {
        for (j = 1; j < n; j++) {
            r[j] = r[j-1] + r[j];
        }
    }
    return r[n-1];
}