char * addBinary(char * a, char * b){
    if (a == NULL) return b;
    if (b == NULL) return a;

    int alen = strlen(a);
    int blen = strlen(b);

    if (alen < blen) return addBinary(b, a);

    /* a 的长度大于等于 b */
    int aend = alen - 1;
    int bend = blen - 1;
    char *ans = (char*)malloc(sizeof(char) * (alen + 2));
    int ansEnd = 0;
    int carry = 0;
    int num;

    while (aend >= 0 && bend >= 0) {
        num = a[aend] - '0' + b[bend] - '0' + carry;
        ans[ansEnd++] = num % 2 + '0';
        carry = num / 2;
        aend -= 1;
        bend -= 1;
    }

    while (aend >= 0) {
        num = a[aend] - '0' + carry;
        ans[ansEnd++] = num % 2 + '0';
        carry = num / 2;
        aend -= 1;
    }

    if (carry) {
        ans[ansEnd++] = carry + '0';
    }

    ans[ansEnd] = '\0';

    int left = 0;
    int right = ansEnd - 1;
    char tmp;
    while (left < right) {
        tmp = ans[left];
        ans[left] = ans[right];
        ans[right] = tmp;
        left += 1;
        right -= 1;
    }
    return ans;
}