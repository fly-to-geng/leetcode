# [838. 推多米诺](https://leetcode-cn.com/problems/push-dominoes/)

## 题目描述

一行中有 N 张多米诺骨牌，我们将每张多米诺骨牌垂直竖立。

在开始时，我们同时把一些多米诺骨牌向左或向右推。

![](https://aliyun-lc-upload.oss-cn-hangzhou.aliyuncs.com/aliyun-lc-upload/uploads/2018/05/19/domino.png)

每过一秒，倒向左边的多米诺骨牌会推动其左侧相邻的多米诺骨牌。

同样地，倒向右边的多米诺骨牌也会推动竖立在其右侧的相邻多米诺骨牌。

如果同时有多米诺骨牌落在一张垂直竖立的多米诺骨牌的两边，由于受力平衡， 该骨牌仍然保持不变。

就这个问题而言，我们会认为正在下降的多米诺骨牌不会对其它正在下降或已经下降的多米诺骨牌施加额外的力。

给定表示初始状态的字符串 "S" 。如果第 i 张多米诺骨牌被推向左边，则 S[i] = 'L'；如果第 i 张多米诺骨牌被推向右边，则 S[i] = 'R'；如果第 i 张多米诺骨牌没有被推动，则 S[i] = '.'。

返回表示最终状态的字符串。

示例 1：

    输入：".L.R...LR..L.."
    输出："LL.RR.LLRRLL.."

示例 2：

    输入："RR.L"
    输出："RR.L"
    说明：第一张多米诺骨牌没有给第二张施加额外的力。

提示：

    0 <= N <= 10^5
    表示多米诺骨牌状态的字符串只含有 'L'，'R'; 以及 '.';

## 解题思路

暴力方法，分情况讨论，可以通过全部用例

```c
char *pushDominoes(char *dominoes)
{
    if (dominoes == NULL)
        return NULL;

    // start指向前面的LR，end指向后面的LR
    int n = strlen(dominoes);
    int start = -1;
    int end = -1;
    char *ans = (char *)malloc(sizeof(char) * (n + 2));
    int ansEnd = 0;
    for (int i = 0; i < n; i++)
    {
        if (dominoes[i] == 'L' || dominoes[i] == 'R')
        {
            ans[ansEnd++] = dominoes[i];
        }
        else
        {
            start = i - 1;
            while (start >= 0)
            {
                if (dominoes[start] == 'L' || dominoes[start] == 'R')
                {
                    break;
                }
                start--;
            }
            end = i + 1;
            while (end < n)
            {
                if (dominoes[end] == 'L' || dominoes[end] == 'R')
                {
                    break;
                }
                end++;
            }
            if (start < 0 && end >= n)
            {
                ans[ansEnd++] = dominoes[i];
            }
            else if (start < 0)
            {
                if (dominoes[end] == 'L')
                {
                    ans[ansEnd++] = dominoes[end];
                }
                else
                {
                    ans[ansEnd++] = dominoes[i];
                }
            }
            else if (end >= n)
            {
                if (dominoes[start] == 'R')
                {
                    ans[ansEnd++] = dominoes[start];
                }
                else
                {
                    ans[ansEnd++] = dominoes[i];
                }
            }
            else
            {
                int ll = i - start;
                int rr = end - i;
                if (dominoes[start] == 'L' && dominoes[end] == 'R')
                {
                    ans[ansEnd++] = dominoes[i];
                }
                else if (dominoes[start] == dominoes[end])
                {
                    ans[ansEnd++] = dominoes[start];
                }
                else if (ll == rr)
                {
                    ans[ansEnd++] = dominoes[i];
                }
                else if (ll > rr)
                {
                    if (dominoes[end] == 'L')
                    {
                        ans[ansEnd++] = dominoes[end];
                    }
                    else
                    {
                        ans[ansEnd++] = dominoes[i];
                    }
                }
                else if (ll < rr)
                {
                    if (dominoes[start] == 'R')
                    {
                        ans[ansEnd++] = dominoes[start];
                    }
                    else
                    {
                        ans[ansEnd++] = dominoes[i];
                    }
                }
            }
        }
    }
    ans[ansEnd] = '\0';
    return ans;
}
```

修改一下策略，每次记录前后的情况，可以省很多。

```c
char *pushDominoes(char *dominoes)
{
    if (dominoes == NULL)
        return NULL;

    // start指向前面的LR，end指向后面的LR
    int n = strlen(dominoes);
    int start = -1;
    int end = -1;
    char *ans = (char *)malloc(sizeof(char) * (n + 2));
    int ansEnd = 0;
    for (int i = 0; i < n; i++)
    {
        if (dominoes[i] == 'L' || dominoes[i] == 'R')
        {
            ans[ansEnd++] = dominoes[i];
            start = i;
        }
        else
        {
            // 如果end小于当前索引，向后查找确定end的位置
            if (end < i)
            {
                end = i + 1;
                while (end < n && dominoes[end] == '.')
                    end++;
            }

            if (start < 0 && end >= n)
            {
                ans[ansEnd++] = '.';
            }
            else if (start < 0 && dominoes[end] == 'L')
            {
                ans[ansEnd++] = 'L';
            }
            else if (start < 0 && dominoes[end] != 'L')
            {
                ans[ansEnd++] = '.';
            }
            else if (end >= n && dominoes[start] == 'R')
            {
                ans[ansEnd++] = 'R';
            }
            else if (end >= n && dominoes[start] != 'R')
            {
                ans[ansEnd++] = '.';
            }
            else if (dominoes[start] == dominoes[end])
            {
                ans[ansEnd++] = dominoes[start];
            }
            else if (dominoes[start] == 'L' && dominoes[end] == 'R')
            {
                ans[ansEnd++] = '.';
            }
            else
            {
                int ll = i - start;
                int rr = end - i;
                if (ll == rr)
                {
                    ans[ansEnd++] = '.';
                }
                else if (ll < rr)
                {
                    ans[ansEnd++] = dominoes[start];
                }
                else
                {
                    ans[ansEnd++] = dominoes[end];
                }
            }
        }
    }
    ans[ansEnd] = '\0';
    return ans;
}
```
