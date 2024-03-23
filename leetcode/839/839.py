from typing import List
# 34 / 63 个通过测试用例
class Solution:
    def create(self, n):
        self.array = [i for i in range(n)]
        self.n = n
    
    def parent(self, i):
        """ 返回i的根节点
        array[i] 中存放 i的根， 如果 array[i] == i, 说明这个点是根节点
        否则， array
        """
        if self.array[i] == i:
            return i
        self.array[i] = self.parent(self.array[i])
        return self.array[i]

    def merge(self, i, j):
        """
        合并i,j为一组，如果已经是一组，无影响
        """
        if i > j:
            return self.merge(j, i)
        pi = self.parent(i)
        pj = self.parent(j)
        if pi != pj:
            self.array[pj] = pi
            self.n -= 1
    def count(self):
        """
        返回不同的集合数量
        """
        return self.n
    def numSimilarGroups(self, A: List[str]) -> int:
        def similar(a, b):
            m = len(a)
            n = len(b)
            if m != n: return False
            cc = 0
            for i in range(n):
                if a[i] != b[i]:
                    cc += 1
                if cc > 2:
                    break
            if cc == 2 or cc == 0:
                return True
            return False
        n = len(A)
        if n == 0: return 0
        self.create(n)
        for i in range(n-1):
            for j in range(i + 1, n):
                if i != j and similar(A[i], A[j]):
                    self.merge(i, j)
        return self.n

s = Solution()
A = ["tars","rats","arts","star"]
expected = 2
ans = s.numSimilarGroups(A)
assert ans == expected

end = 1