# [890. 查找和替换模式](https://leetcode-cn.com/problems/find-and-replace-pattern/)

## 题目描述

你有一个单词列表 words 和一个模式  pattern，你想知道 words 中的哪些单词与模式匹配。

如果存在字母的排列 p ，使得将模式中的每个字母 x 替换为 p(x) 之后，我们就得到了所需的单词，那么单词与模式是匹配的。

（回想一下，字母的排列是从字母到字母的双射：每个字母映射到另一个字母，没有两个字母映射到同一个字母。）

返回 words 中与给定模式匹配的单词列表。

你可以按任何顺序返回答案。

 

示例：

      输入：words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
      输出：["mee","aqq"]
      解释：
      "mee" 与模式匹配，因为存在排列 {a -> m, b -> e, ...}。
      "ccc" 与模式不匹配，因为 {a -> c, b -> c, ...} 不是排列。
      因为 a 和 b 映射到同一个字母。
 

提示：

      1 <= words.length <= 50
      1 <= pattern.length = words[i].length <= 20

## 解题思路

```c
#define N 26

int map[N];
int unique[N];
void init(int *array, int value)
{
    int i;
    for (i = 0; i < N; i++) {
        array[i] = value;
    }
}
int isMatch(char *str, char *pattern)
{
    int i;
    char a, b;
    int aa, bb;
    
    int n1 = strlen(str);
    int n2 = strlen(pattern);
    if (n1 != n2) {
        return false;
    }

    for (i = 0; i < n1; i++) {
        a = str[i];
        b = pattern[i];
        aa = a - 'a';
        bb = b - 'a';
        if (map[aa] == -1) {
            map[aa] = bb;
        } else if (map[aa] != bb) {
            return false;
        }
        if (unique[bb] == -1) {
            unique[bb] = aa;
        } else if (unique[bb] != aa) {
            return false;
        }
    }
    return true;    
}
char *copystr(char *str)
{
    int n = strlen(str);
    int i;
    char *newstr;
    newstr = (char*)malloc(sizeof(char) * (n + 1));
    for (i = 0; i < n; i++) {
        newstr[i] = str[i];
    }
    newstr[i] = '\0';
    return newstr;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findAndReplacePattern(char ** words, int wordsSize, char * pattern, int* returnSize){
    int i;
    char **ans;
    int ansEnd = 0;
    ans = (char**)malloc(sizeof(char*) * wordsSize);
    for (i = 0; i < wordsSize; i++) {
        init(map, -1);
        init(unique, -1);
        if (isMatch(words[i], pattern)) {
            ans[ansEnd++] = copystr(words[i]);
        }
    }
    *returnSize = ansEnd;
    return ans;
}
```
