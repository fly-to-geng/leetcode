## [3. 无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)

### 题目描述

给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

**示例**

```
示例 1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
```

### 解题思路

1. 先尝试暴力的解法，从第一字符开始放入set,遇到重复的就停止，记录当前不重复的最大字符个数，最后输出一个最大的。

2. 暴力方法使用了两重循环，其中有大量的无用查找。仔细考虑，如果扫描到一样的，可以从左侧删除一样的，继续向下扫描，这样就可以不用回溯，提高效率。
### 题解

#### C++

暴力解决：

```c
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.size();
        set<char> unique;
        int ans = 0;
        
        for (int i = 0; i < len; i ++)
        {
            int length;
            for (int j = i; j < len; j ++)
            {
                if (unique.find(s[j]) == unique.end())
                {
                    unique.insert(s[j]);
                }
                else
                {
                    break;
                }
            }
            length = unique.size();
            ans = ans > length ? ans : length;
            unique.clear();
        }
        return ans;
    }
};
```

使用哈希表记录元素位置，避免重复扫描。

```c
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> m;
        int ans = 0;
        int left = 0; // 指示左侧开始的位置
        for (int i = 0; i < s.size(); i++)
        {
            left = max(left, m[ s[i] ]); //更新左侧
            m[ s[i] ] = i + 1; // 位置从1开始
            ans = max(ans, i - left + 1);
        }
        return ans;
    }
};
```

#### python

```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        j = 0
        end = len(s)
        ans = 0
        unique = set()

        while(j < end):
            i = j
            while(i < end):
                if s[i] not in unique:
                    unique.add(s[i])
                    i = i + 1
                    continue
                else:
                    break
            length = len(unique)
            ans = max(ans, length)
            unique = set()
            j = j + 1
            
        return ans
 ```
 
 使用dict存储映射关系，实现一遍扫描出结果。
 
 ```python
 class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        ans = 0
        m = {}
        left = 0
        for i, v in enumerate(s):
            if v not in m:
                m[v] = i + 1
            else:
                left = max(left, m[v])
                m[v] = i + 1
            ans = max(ans, i - left + 1)
        return ans
```