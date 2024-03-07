# [1016. 子串能表示从 1 到 N 数字的二进制串](https://leetcode-cn.com/problems/binary-string-with-substrings-representing-1-to-n/)

## 题目描述

给定一个二进制字符串 S（一个仅由若干 '0' 和 '1' 构成的字符串）和一个正整数 N，如果对于从 1 到 N 的每个整数 X，其二进制表示都是 S 的子串，就返回 true，否则返回 false。

示例 1：

        输入：S = "0110", N = 3
        输出：true

示例 2：

        输入：S = "0110", N = 4
        输出：false
 

提示：

        1 <= S.length <= 1000
        1 <= N <= 10^9

## 解题思路

字符串查找

```c++
#define PN 100
int next[PN];
int nextEnd = 0;

// 计算模式串的 next 数组
void computeNext(const char *pattern)
{
    int i;
    int j = -1;
    const int n = strlen(pattern);
    next[0] = j;
    for (i = 1; i < n; i++) {
        while (j > -1 && pattern[j+1] != pattern[i]) {
            j = next[j];
        }
        if (pattern[i] == pattern[j + 1]) {
            j++;
        }
        next[i] = j;
    }
    nextEnd = n;
}

int kmp(const char *string, const char *pattern)
{
    int i;
    int j = -1;
    const int n = strlen(string);
    const int m = strlen(pattern);
    if (m == 0 && n == 0) return 0;
    if (m == 0) return 0;
    computeNext(pattern);
    for (i = 0; i < n; i++) {
        while (j > -1 && pattern[j+1] != string[i]) {
            j = next[j];
        }
        if (string[i] == pattern[j + 1]) {
            j++;
        }
        if (j == m - 1) {
            return i - j;
        }
    }
    return -1;
}
bool find(char *S, int i)
{
    const int n = strlen(S);
    char num[32];
    char tmp;
    int k = 0;
    while (i) {
        num[k++] = (char)(i & 1) + '0';
        i = i >> 1;
    }
    num[k] = '\0';
    int a = 0;
    int b = k - 1;
    while (a < b) {
        tmp = num[a];
        num[a] = num[b];
        num[b] = tmp;
        a++;
        b--;
    }
    int result;
    result = kmp(S, num);
    if (result == -1) {
        return false;
    }
    return true;
}
bool queryString(char * S, int N){
    int i;
    for (i = 1; i <= N; i++) {
        if (!find(S, i)) {
            return false;
        }
    }
    return true;
}
```