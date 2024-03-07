## [5. 最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/)

### 题目描述

给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

**示例**

```
示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。


示例 2：

输入: "cbbd"
输出: "bb"
```

### 解题思路1

暴力方法，分别以每个字符为中心查找最长的回文串，保存最长的那个的下标，返回。
时间复杂度O(n^2),可以通过。

#### C++

```c++
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() <= 1) return s;
        int start = 0, end = 0;

        for (int i = 0; i < s.size(); i++)
        {
            int left, right, tmpLen = 0;
            // 以s[i]为中心的最长回文串
            left = right = i;
            while (left >= 0 && right < s.size() && s[left] == s[right])
            {
                left--, right++;
            }
            tmpLen = max(tmpLen, right - left - 1);
            // 以s[i],s[i+1]为中心的最长回文串
            left = i, right = i + 1;
            while (left >= 0 && right < s.size() && s[left] == s[right])
            {
                left--, right++;
            }
            tmpLen = max(tmpLen, right - left - 1);
            // 如果本次找到的比之前的长，更新start, end
            if (tmpLen > end - start + 1)
            {
                start = i - (tmpLen - 1) / 2;
                end = i + tmpLen / 2;
            }
        }
        return s.substr(start, end-start+1);
    }
};
```

#### python

```python
class Solution:
    def longestPalindrome(self, s: str) -> str:
        start = 0
        end = 0
        for i in range(len(s)):
            tmp_max = 0
            # s[i]为中心的最长回文串
            left = i
            right = i
            while left >= 0 and right < len(s) and s[left]==s[right]:
                left -= 1
                right += 1
            tmp_max = max(tmp_max, right - left - 1)
            # s[i], s[i+1]为中心的最长回文串
            left = i
            right = i + 1
            while left >= 0 and right < len(s) and s[left]==s[right]:
                left -= 1
                right += 1
            tmp_max = max(tmp_max, right - left - 1)
            # 如果本次找到的比之前的长，更新记录的下标
            if tmp_max > end - start + 1:
                start = i - (tmp_max - 1) // 2
                end = i + tmp_max // 2
        return s[start : end+1]
```

### 解题思路2

使用Manacher算法可以达到O(n)的时间复杂度。

https://segmentfault.com/a/1190000008484167


#### python

```python
class Solution(object):
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        # 预处理字符串，每个间隔中插入一个未出现的字符 '#'
        s = '#' + "".join([c + '#' for c in s])
        s = '^' + s + '$' # 首尾附加不同字符避免边界判断
        n = len(s)
        lps = [1] * n

        lid, mid, rid = 0, 0, 0
        i = 1 # s[0] 是 '^'没有必要计算
        center = 0 # 记录最长回文中心位置，用来生成回文
        ans = 0 # 最长回文的长度
        while i < n - 1:
            if i < rid:
                # i' = 2 * mid - i 是 i 关于 mid 的对称点
                lps[i] = min(lps[2 * mid - i], rid - i)

            # lps[i] 初始化为1，因为任意一个字符都是半径为1的回文
            # 以 i 为中心向两边扩展，直到不能再扩展为止
            # 因为首尾新增了两个不一样的字符，所以到边界一定会停止
            while s[i - lps[i]] == s[i + lps[i]]:
                lps[i] += 1

            # 通过上面的循环，我们已经计算出 lps[i]
            # 如果 i + lps[i] > rid, 说明经过扩展边界已经超过 rid
            # 更新 mid 为 i, 因为 lps[i] 已经计算得到
            # 更新 rid 为 mid + lps[mid]
            if rid < i + lps[i]:
                mid = i
                rid = mid + lps[mid]

            if ans < lps[i] - 1:
                ans = lps[i] - 1
                center = i
            # 如果 i + lps[i] < rid, 说明 i 的边界还没有越过 mid 的边界
            # 可以继续计算 i + 1, 依旧利用 mid 的堆称信息
            i += 1

        string = s[center-ans : center + ans]
        string = string.replace("#", "")
        return string
 ```
