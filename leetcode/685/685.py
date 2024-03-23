from typing import List

N = 1000

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
    def isValid(self, edges, i):
        """
        删除边edges[i]之后图是否连通
        """
        self.create(len(edges))
        for j in range(len(edges)):
            if j != i:
                pu = self.parent(edges[j][0] - 1)
                pv = self.parent(edges[j][1] - 1)
                if pu != pv:
                    self.merge(edges[j][0] - 1, edges[j][1] - 1)
        return self.n == 1

    def findRedundantDirectedConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges) # 节点数量
        enterPoints = [0 for _ in range(n)] # 每个节点的入度
        for i in range(n):
            enterPoints[ edges[i][1] - 1 ] += 1 # 题目中的点编号从1开始
        for i in reversed(range(n)):
            if enterPoints[ edges[i][1] - 1 ] == 2:
                ans = self.isValid(edges, i)
                if ans == True:
                    return edges[i]
        for i in reversed(range(n)):
            if enterPoints[ edges[i][1] - 1 ] == 1:
                ans = self.isValid(edges, i)
                if ans == True:
                    return edges[i]
        return []

s = Solution()
edges =  [[1,2], [2,3], [3,4], [4,1], [1,5]]
ans = s.findRedundantDirectedConnection(edges)

end = 10
            