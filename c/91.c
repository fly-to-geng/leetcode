void dfs(char *s, int i, int *ans)
{
    int num;

    if (i == strlen(s)) {
        (*ans)++;
        return;
    }
    // 消耗一个数字
    num = s[i] - '0';
    if (num < 1 || num > 9) {
        return;
    } else {
        dfs(s, i + 1, ans);
    }

    // 消耗两个数字
    if (i + 1 < strlen(s)) {
        num = (s[i] - '0') * 10 + (s[i + 1] - '0');
        if (num >= 1 && num <= 26) {
            dfs(s, i + 2, ans);
        }
    }
    return;
}
int numDecodings(char * s){
    int ans = 0;
    dfs(s, 0, &ans);
    return ans;
}