int minDeletionSize(char ** A, int ASize){
    int ans = 0;
    int i;
    int j;
    int n = strlen(A[0]);

    for (i = 0; i < n; i++) {
        bool flag = false;
        for (j = 1; j < ASize; j++) {
            if (A[j][i] < A[j - 1][i]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            ans++;
        }
    }
    return ans;
}