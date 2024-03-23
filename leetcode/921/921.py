class Solution:
    def minAddToMakeValid(self, S: str) -> int:
        ans = 0
        stack = [] 
        for c in S:
            if c == '(':
                stack.append(c)
            else:
                if len(stack) > 0:
                    stack.pop()
                else:
                    ans += 1
        ans += len(stack)
        return ans

s = Solution()
ans = s.minAddToMakeValid("(()())))(")
print(ans)