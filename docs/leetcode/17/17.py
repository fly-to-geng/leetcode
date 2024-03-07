
from typing import List

class Solution:
    def __init__(self):
        self.t9 = ["abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"]

    def dfs(self, start, digits, line, ans):
        if start == len(digits):
            ans.append(''.join(line))
            return
        curr = self.t9[int(digits[start]) - 2]
        for c in curr:
            line.append(c)
            self.dfs(start + 1, digits, line, ans)
            line.pop()
        return

    def letterCombinations(self, digits: str) -> List[str]:
        ans = []
        
        if len(digits) == 0:
            return ans

        line = []
        self.dfs(0, digits, line, ans)
        return ans

digits = "23"
s = Solution()
ans = s.letterCombinations(digits)
print(ans)
