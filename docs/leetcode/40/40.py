# -*- coding:utf-8 -*-

from typing import List 

class Solution:
    def dfs(self, start, target, candidates, line, ans):
        if target == 0:
            print(line)
            ans.append(line[:])
            return
        if start == len(candidates):
            return
        for i in range(start, len(candidates)):
            if i > start and candidates[i] == candidates[i - 1]:
                continue
            if candidates[i] > target:
                break
            line.append(candidates[i])
            self.dfs(i + 1, target - candidates[i], candidates, line, ans)
            line.pop()
        return

    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        ans = []
        if len(candidates) == 0:
            return ans
        
        candidates = sorted(candidates)
        
        line = []
        for i in range(len(candidates)):
            if i > 0 and candidates[i] == candidates[i - 1]:
                continue
            if candidates[i] > target:
                break
            line.append(candidates[i])
            self.dfs(i + 1, target - candidates[i], candidates, line, ans)
            line.pop()
        return ans

s = Solution()
ans = s.combinationSum2([10,1,2,7,6,1,5], 8)
print(ans)