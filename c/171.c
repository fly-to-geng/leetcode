int titleToNumber(char * s){
    int n = strlen(s);
    long long base = 1;
    int i;
    long long num;
    long long ans = 0;

    for (i = n - 1; i >= 0; i--) {
        num = s[i] - 'A' + 1;
        ans += num * base;
        base = base * 26;
    }
    return (int)ans;
}