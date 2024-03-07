#define max(a, b) ((a) > (b) ? (a) : (b))
int longestOnes(int* A, int ASize, int K){
    int start = 0;
    int ans = 0;
    int max_count = 0;
    // [start, end] 内有 max_count 个1
    for(int end = 0; end < ASize; end++) {
        if (A[end] == 1) {
            max_count += 1;
        }
        // 当0的个数大于K的个数的时候，向右滑动
        if (end - start + 1 - max_count > K) {
            if (A[start] == 1) {
                max_count -= 1;
            }
            start++;    
        }
        ans = max(ans, end - start + 1);
    }
    return ans;
}