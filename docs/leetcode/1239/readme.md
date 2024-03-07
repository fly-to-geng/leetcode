# [1239. 串联字符串的最大长度](https://leetcode-cn.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/)

## 题目描述

给定一个字符串数组 arr，字符串 s 是将 arr 某一子序列字符串连接所得的字符串，如果 s 中的每一个字符都只出现过一次，那么它就是一个可行解。

请返回所有可行解 s 中最长长度。

 

示例 1：

        输入：arr = ["un","iq","ue"]
        输出：4
        解释：所有可能的串联组合是 "","un","iq","ue","uniq" 和 "ique"，最大长度为 4。

示例 2：

        输入：arr = ["cha","r","act","ers"]
        输出：6
        解释：可能的解答有 "chaers" 和 "acters"。

示例 3：

        输入：arr = ["abcdefghijklmnopqrstuvwxyz"]
        输出：26
 

提示：

        1 <= arr.length <= 16
        1 <= arr[i].length <= 26
        arr[i] 中只含有小写英文字母

## 解题思路

```c++
#define MAX(a,b) ((a) > (b) ? (a) : (b))
int size = 0;

// 字符串转换成数字
int char2int(char *string)
{
    int ans = 0;
    while (*string) {
        ans += 1 << (*string - 'a');
    }
    return ans;
}
// 返回把string中字母加入集合set中的结果
int add(char *string, int set)
{
    int ans = char2int(string);
    ans = ans | set;
    return ans;
}

// 返回string中的任意一个字母是否在set中出现过
int notCanPut(char* string, int set)
{
    int ans = char2int(string);
    ans = ans & set;
    return ans;
}
/*
 * arr[i] 当前检查的单词
 * currentSet : 当前加入的集合
 * oneAns : 深度搜索到底一趟的结果
 * ans : 保存最终的结果
 */
void dfs(char** arr, int i, int currentSet, int *oneAns, int *ans)
{
    // 如果到达了末尾，比较一趟的结果和最终的结果大小
    if (i == size) {
        *ans = MAX(*ans, *oneAns);
        return;
    }

    // 如果arr[i]无法放入，则搜索下一个单词
    if (notCanPut(arr[i], currentSet)) {
        dfs(arr, i+1, currentSet, oneAns, ans);
        return;
    }

    // 如果arr[i]可以放入，那么放入和不放入两种情况都需要递归
    int tmpOneAns = *oneAns + strlen(arr[i]);
    dfs(arr, i + 1, add(arr[i], currentSet), &tmpOneAns, ans);

    dfs(arr, i + 1, currentSet, oneAns, ans);

    return;
}
int maxLength(char ** arr, int arrSize){
    int ans = 0;
    int oneAns = 0;
    int currentSet = 0;

    size = arrSize;
    dfs(arr, 0, &oneAns, &ans);
    return ans;
}
```