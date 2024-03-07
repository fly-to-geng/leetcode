# [1023. 驼峰式匹配](https://leetcode-cn.com/problems/camelcase-matching/)

## 题目描述

如果我们可以将小写字母插入模式串 pattern 得到待查询项 query，那么待查询项与给定模式串匹配。（我们可以在任何位置插入每个字符，也可以插入 0 个字符。）

给定待查询列表 queries，和模式串 pattern，返回由布尔值组成的答案列表 answer。只有在待查项 queries[i] 与模式串 pattern 匹配时， answer[i] 才为 true，否则为 false。

 

示例 1：

        输入：queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
        输出：[true,false,true,true,false]
        示例：
        "FooBar" 可以这样生成："F" + "oo" + "B" + "ar"。
        "FootBall" 可以这样生成："F" + "oot" + "B" + "all".
        "FrameBuffer" 可以这样生成："F" + "rame" + "B" + "uffer".

示例 2：

        输入：queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
        输出：[true,false,true,false,false]
        解释：
        "FooBar" 可以这样生成："Fo" + "o" + "Ba" + "r".
        "FootBall" 可以这样生成："Fo" + "ot" + "Ba" + "ll".

示例 3：

        输出：queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
        输入：[false,true,false,false,false]
        解释： 
        "FooBarTest" 可以这样生成："Fo" + "o" + "Ba" + "r" + "T" + "est".

## 解题思路

```c++
#define N 1001
bool isMatch(char *s, char *pattern)
{
    int n = strlen(s);
    int m = strlen(pattern);
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (s[i] == pattern[j]) {
            i++;
            j++;
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            i++;
        } else {
            return false;
        }
    }
    if (j < m) {
        return false;
    }
    if (i < n) {
        while (i < n) {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                return false;
            }
            i++;
        }
    }
    return true;
}
bool* camelMatch(char ** queries, int queriesSize, char * pattern, int* returnSize){
    bool *ans;
    bool ansOne;
    int i;
    int ansEnd = 0;
    ans = (bool*)malloc(sizeof(bool) * N);
    for (i = 0; i< queriesSize; i++) {
        if (isMatch(queries[i], pattern)) {
            ans[ansEnd++] = true;
        } else {
            ans[ansEnd++] = false;
        }
    }
    (*returnSize) = ansEnd;
    return ans;
}
```