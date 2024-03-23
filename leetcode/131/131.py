# -*- coding:utf-8 -*-

from typing import List 

class Solution:
    def isHuiWen(self, s, begin, end):
        while begin < end:
            if s[begin] != s[end]:
                return False
            begin += 1
            end -= 1
        return True

    def dfs(self, begin, end, s, line, ans):
        if end == len(s):
            if begin == end:
                ans.append(line[:])
            return
        if self.isHuiWen(s, begin, end):
            line.append(s[begin : end+1])
            self.dfs(end+1, end+1, s, line, ans)
            line.pop()
        self.dfs(begin, end+1, s, line, ans)
        return

    def partition(self, s: str) -> List[List[str]]:
        line = []
        ans = []
        self.dfs(0, 0, s, line, ans)
        return ans

s = Solution()
ans = s.partition("aab")
print(ans)