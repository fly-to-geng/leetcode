void reverse(char *s, int start, int end)
{
    char tmp;
    while (start < end) {
        tmp = s[start];
        s[start] = s[end];
        s[end] = tmp;
        start++;
        end--;
    }
}
char * reverseStr(char * s, int k){
    int n = strlen(s);
    int count2k = n / (2 * k);
    int last = n - count2k * k * 2;
    int start = -1;
    int end = -1;
    int i;
    for (i = 0; i < count2k; i++) {
        start = i * 2 * k;
        end = start + k - 1;
        reverse(s, start, end);
    }
    start = count2k * 2 * k;
    if (last >= k) {
        end = start + k - 1;
        reverse(s, start, end);
    } else {
        end = n - 1;
        reverse(s, start, end);
    }

    return s;
}