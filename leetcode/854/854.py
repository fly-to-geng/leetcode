class Solution:
    def kSimilarity(self, A: str, B: str) -> int:
        def diff(str1, str2):
            for i in range(len(str1)):
                if str1[i] != str2[i]:
                    return i
            return len(str1)
        def swap(str, i, j):
            tmp = list(str)
            tmp[i], tmp[j] = tmp[j], tmp[i]
            return "".join(tmp)
        
        deque = [ A ]
        seen = set()
        seen.add(A)
        ans = 0
        while len(deque) > 0:
            # 每次取出队列中所有元素，作为一层
            size = len(deque)
            for _ in range(size):
                curr = deque.pop(0)
                if curr == B: return ans
                s = diff(curr, B)
                for j in range(s + 1, len(A)):
                    # 此处注意，要选择curr, B, s, j 互不相同的进行下一个查找
                    if curr[j] == B[s] and curr[j] != B[j]:
                        nextStr = swap(curr, s, j)
                        # 如果已经搜索过这个单词，不要再继续搜索，因为之前搜索过的结果肯定更小
                        if nextStr not in seen:
                            deque.append(nextStr)
                            seen.add(nextStr)
            ans += 1
        return ans

s = Solution()
A = "cdebcdeadedaaaebfbcf"
B = "baaddacfedebefdabecc"
ans = s.kSimilarity(A, B)

end = 10