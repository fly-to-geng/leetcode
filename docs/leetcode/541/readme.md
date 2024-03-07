# [541. 反转字符串 II](https://leetcode-cn.com/problems/reverse-string-ii/)

## 题目描述

给定一个字符串 s 和一个整数 k，你需要对从字符串开头算起的每隔 2k 个字符的前 k 个字符进行反转。

如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
 

示例:

    输入: s = "abcdefg", k = 2
    输出: "bacdfeg"
 

提示：

    该字符串只包含小写英文字母。
    给定字符串的长度和 k 在 [1, 10000] 范围内。

## 解题思路

```c
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
```
