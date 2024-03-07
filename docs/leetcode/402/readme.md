# [402. 移掉K位数字](https://leetcode-cn.com/problems/remove-k-digits/)

## 题目描述

给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。

注意:

num 的长度小于 10002 且 ≥ k。
num 不会包含任何前导零。

示例 1 :

    输入: num = "1432219", k = 3
    输出: "1219"
    解释: 移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219。

示例 2 :

    输入: num = "10200", k = 1
    输出: "200"
    解释: 移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。

示例 3 :

    输入: num = "10", k = 2
    输出: "0"
    解释: 从原数字移除所有的数字，剩余为空就是0。

## 解题思路

```c
char *removeKdigits(char *num, int k)
{
    int n = strlen(num);
    int l = n - k;

    // 从 num 中选择 l 个数字组成 最小的数
    char *ans = (char *)malloc(sizeof(char) * (l + 3));
    int ansEnd = 0;

    // 全部移除的情况下返回0
    if (l == 0)
    {
        ans[0] = '0';
        ans[1] = '\0';
        return ans;
    }

    int start = 0;
    int end = n - l;
    // 每次从[start, end]中选择最小的那个， 更新 start 为index+1, end = end+1
    while (start <= end && start < n && end < n)
    {
        int min = INT_MAX;
        int index = -1;
        for (int i = start; i <= end; i++)
        {
            if (num[i] < min)
            {
                min = num[i];
                index = i;
            }
        }
        if (index != -1)
        {
            if (ansEnd == 0 && num[index] == '0')
            {
                start = index + 1;
                end = end + 1;
            }
            else
            {
                ans[ansEnd++] = num[index];
                start = index + 1;
                end = end + 1;
            }
        }
        else
        {
            break;
        }
    }
    // 只选择了前导0的情况下返回0
    if (ansEnd == 0)
    {
        ans[ansEnd++] = '0';
    }
    ans[ansEnd] = '\0';
    return ans;
}
```
