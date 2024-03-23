class Solution:
    def longestSubsequence(self, arr: List[int], difference: int) -> int:
        n = len(arr)
        if n == 0: return 0
        dp = [1 for _ in range(n)]
        dic = {}
        
        dic[arr[0]] = 1
        for i in range(1, n):
            number = arr[i] - difference
            if number in dic:
                dp[i] = dic[number] + 1
                dic[arr[i]] = dp[i]
            else:
                dp[i] = 1
                dic[arr[i]] = 1
        return max(dp)