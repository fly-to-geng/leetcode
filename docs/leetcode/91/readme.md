# [91. 解码方法](https://leetcode-cn.com/problems/decode-ways/)

## 题目描述

一条包含字母 A-Z 的消息通过以下方式进行了编码：

'A' -> 1
'B' -> 2
...
'Z' -> 26
给定一个只包含数字的非空字符串，请计算解码方法的总数。

示例 1:

    输入: "12"
    输出: 2
    解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。

示例 2:

    输入: "226"
    输出: 3
    解释: 它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。

## 解题思路

很容易想到，用DFS的方式在每个可以分割的地方尝试是否分割。 例如 s = "123412", i = 0时 1 --> A 可以解码， 可以从这里断开， 也可以不断开 12 --> L.

```c
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
    //dfs(s, 0, &ans);
    return ans;
}
```

239 / 258 个通过测试用例. 这种方法存在大量的重复计算，无法通过所有用例。

把上面的用例按照递归过程展开

```yml
1 - 1 
2	- 2
3		  - 3
4			  - 4
5				  - 1 
6					    - 2   --> 1,2,3,4,1,2
7				  - 12      --> 1,2,3,4,12
8	- 23
9		  - 4
10			- 1
11				  - 2      --> 1,23,4,1,2
12			- 12         --> 1,23,4,12
13 - 12
14		- 3
15			- 4
16				- 1
17					  - 2      --> 12,3,4,1,2
18				- 12         --> 12,3,4,12
```

可以发现3-7行与14-18行是完全一致的， 当字符串长的时候，这种重复计算更加明显， 这启发我们减少重复计算，从而提高效率。 
下面我们尝试从后面开始向前进行解码，记录已经获得的解码数量，用来避免重复计算。

```c
/*
    设dp[i] 表示 s[i...n) 解码的数量， dp[n] = 0, dp[n-1] = 1 if dp[n-1] in [1,9] else dp[n-1] = 0
    "0" 不能解码， "01" 也不能解码
    dp[n-2] = dp[n] if s[n-2] s[n-1] in [1, 26], 对应情况是 s[n-1], s[n-2] 两个数字解码成一个字母
            = dp[n-1], 对应情况是 s[n-2] 单独解码成一个字母
    dp[n-2] 就是以上两种情况的和 
*/
int numDecodings(char * s){
    if (s == NULL) return 0;
    int n = strlen(s);
    int nextNext = 1;
    int next = (s[n-1] == '0') ? 0 : 1;
    int curr;
    for (int i = n - 2; i >= 0; i--) {
        if (s[i] == '0') {
            curr = 0; // '0' 无法解码，对应解码方法数量为0
        } else {
            int number = (s[i] - '0') * 10 + s[i + 1] - '0';
            curr = 0;
            if (number >= 1 && number <= 26) {
                curr = nextNext;
            }
            curr += next;
        }

        nextNext = next;
        next = curr;
    }

    return next;
}
```
