from typing import List

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

    def findCircleNum(self, M: List[List[int]]) -> int:
        n = len(M)
        if n == 0: return 0
        self.create(n)
        for i in range(n):
            for j in range(n):
                if i != j and M[i][j] == 1:
                    self.merge(i, j)
        return self.n

s = Solution()
M = [[1,1,0],[1,1,1],[0,1,1]]
ans = s.findCircleNum(M)
end = 10