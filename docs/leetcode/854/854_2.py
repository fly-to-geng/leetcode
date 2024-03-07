
class Solution:
    def kSimilarity(self, A: str, B: str) -> int:
        def swap(str, i, j):
            tmp = list(str)
            tmp[i], tmp[j] = tmp[j], tmp[i]
            return "".join(tmp)
        
        def dfs(i, word, line, ans):
            #print(i, word, line, ans)
            if line > ans:
                return ans
            if i == len(word):
                return line
            if word[i] == B[i]:
                return dfs(i + 1, word, line, ans)

            for j in range(i + 1, n):
                if word[j] == B[i] and word[j] != B[j]:
                    word = swap(word, i, j)
                    minv = dfs(i + 1, word, line + 1, ans)
                    ans = min(ans, minv)
                    word = swap(word, i, j)

            return ans
            
        n = len(A)
        line = 0
        ans = float('inf')
        res = dfs(0, A, line, ans)
        return res

s = Solution()
A = "cdebcdeadedaaaebfbcf"
B = "baaddacfedebefdabecc"
ans = s.kSimilarity(A, B)
end = 10