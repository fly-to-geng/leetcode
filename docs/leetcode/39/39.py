# -*- coding:utf-8 -*-

from typing import List 

class Solution:
    def dfs(self, start, target, line, ans, candidates):
        if target == 0:
            ans.append(line[:])
            return

        for i in range(start, len(candidates)):
            if candidates[i] > target:
                break
            line.append(candidates[i])
            self.dfs(i, target - candidates[i], line, ans, candidates)
            line.pop()
        return

    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        line = []
        ans = []
        if (len(candidates) == 0):
            return ans

        candidates = sorted(candidates)
        self.dfs(0, target, line, ans, candidates)

        return ans

s = Solution()
ans = s.combinationSum([2,7,6,3], 7)
print(ans)