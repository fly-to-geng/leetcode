#define N 10000

char * convertToBase7(int num){
    bool negtive = false;
    int i;
    char *ans;
    int end = 0;
    int tmp;
    char t;
    int left;
    int right;

    ans = (char*)malloc(sizeof(char) * N);

    if (num == 0) {
        ans[0] = '0';
        ans[1] = '\0';
        return ans;
    }
    if (num < 0) {
        num = -num;
        negtive = true;
        ans[end++] = '-';
    }

    while (num > 0) {
        tmp = num % 7;
        num = num / 7;
        ans[end++] = tmp + '0';
    }

    left = negtive ? 1 : 0;
    right = end - 1;
    while (left < right) {
        t = ans[left];
        ans[left] = ans[right];
        ans[right] = t;
        left++;
        right--;
    }
    ans[end] = '\0';
    return ans;
}