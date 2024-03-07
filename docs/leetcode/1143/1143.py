class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        n1 = len(text1)
        n2 = len(text2)
        if n1 == 0 or n2 == 0: return 0

        dp = [ [0 for _ in range(n2 + 1)] for _ in range(n1 + 1) ]
        for i in range(1, n1 + 1):
            for j in range(1, n2 + 1):
                if text1[i - 1] == text2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1] + 1
                else:
                    dp[i][j] = max( dp[i-1][j], dp[i][j-1] )
        return dp[n1][n2]


s = Solution()

text1 = "abcde"
text2 = "ace"
expected = 3
ans = s.longestCommonSubsequence(text1, text2)
assert ans == expected

end = 10
