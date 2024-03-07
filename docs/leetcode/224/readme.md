# [224. 基本计算器](https://leetcode-cn.com/problems/basic-calculator/)

## 题目描述

实现一个基本的计算器来计算一个简单的字符串表达式的值。

字符串表达式可以包含左括号 ( ，右括号 )，加号 + ，减号 -，非负整数和空格  。

示例 1:

    输入: "1 + 1"
    输出: 2

示例 2:

    输入: " 2-1 + 2 "
    输出: 3

示例 3:

    输入: "(1+(4+5+2)-3)+(6+8)"
    输出: 23

说明：

    你可以假设所给定的表达式都是有效的。
    请不要使用内置的库函数 eval。

## 解题思路

按照字符串处理的方式完成解析：

```c
#include <stdio.h>
#include <stdlib.h>
char *substr(char *s, int start, int end)
{
    char *ans = (char*)malloc(sizeof(char) * (end - start + 2));
    int ansEnd = 0;
    for (int i = start; i < end; i++) {
        ans[ansEnd++] = s[i];
    }
    ans[ansEnd++] = '\0';
    return ans;
}
int eval(char *s)
{
    if (s == NULL) return 0;
    const int n = strlen(s);
    int num1 = 0;
    char op = '+';
    int num2;
    int start = 0;
    int end = 0;
    while (end < n) {
        while (start < n && s[start] == ' ') start++;
        if (start >= n) return 0;
        end = start;
        if (s[start] < '0' || s[start] > '9') printf("label1.");
        while (s[end] >= '0' && s[end] <= '9') end++;
        char *num2str = substr(s, start, end); printf("parse str:%s\n", num2str);
        int num2 = atoi(num2str); printf("compute: %d %c %d = \n", num1, op, num2);

        num1 = (op == '+' ? num1 + num2 : num1 - num2);

        start = end;
        while (start < n && s[start] == ' ') start++;
        if (s[start] == '+' || s[start] == '-') op = s[start];
        else printf("label2.\n");

        // 检测是否有连续的运算符，处理负数的情况
        int tmps = start + 1;
        while (tmps < n && s[tmps] == ' ') tmps++;
        if (tmps >= n) printf("lable4.\n");
        if (s[tmps] == '-') {
            if (op == '+') op = '-';
            else if (op == '-') op = '+';
            start = tmps + 1;
            end = start;
        } else {
            start = start + 1;
            end = start;
        }
    }
    return num1;
}

char *toStrWithNegtive(int n)
{
    char *ans = (char*)malloc(sizeof(char) * 100);
    int ansEnd = 0;
    if (n == 0) {
        ans[ansEnd++] = '0';
    } else if (n < 0) {
        n = -n;
        ans[ansEnd++] = '-';
    }
    int start = ansEnd;
    while (n) {
        ans[ansEnd++] = n % 10 + '0';
        n = n / 10;
    }
    ans[ansEnd] = '\0';
    int end = ansEnd - 1;
    char tmp;
    while (start < end) {
        tmp = ans[start];
        ans[start] = ans[end];
        ans[end] = tmp;
        start++;
        end--;
    }
    return ans;
}
int calculate(char *s)
{
    if (s == NULL) return 0;
    const int n = strlen(s);

    char *stack = (char*)malloc(sizeof(char) *(strlen(s) + 10));
    int top = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != ')') {
            stack[top++] = s[i];
        } else {
            int start = i - 1;
            while (start >= 0 && stack[start] != '(') start--;
            if (start < 0) printf("label3.");
            char *cc = substr(stack, start + 1, top); printf("parsed cc: %s\n", cc);
            int tmpnum = eval(cc); printf("parsed cc2:%d\n", tmpnum);
            top = start;
            char *tmpstr = toStrWithNegtive(tmpnum);
            for (int k = 0; k < strlen(tmpstr); k++) {
                stack[top++] = tmpstr[k];
            }
        }
    }
    stack[top] = '\0'; printf("final stack:%s\n", stack);
    return eval(stack);
}
```

如果符号包含的再多一些，添加括号，运算符优先级之后，纯解析字符串可能过于繁琐，这个时候可以使用先将中缀表达式转换成后缀表达式，再利用栈求解最终的结果。
