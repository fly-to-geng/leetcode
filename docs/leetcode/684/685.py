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
    
    def findRedundantDirectedConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges)
        self.create(n)
        ans = None
        for edge in edges:
            if self.parent(edge[0] - 1) != self.parent(edge[1] - 1):
                self.merge(edge[0] - 1, edge[1] - 1)
            else:
                ans = edge
        return ans

s = Solution()
edges = [[1,2], [1,3], [2,3]]
expected = [2,3]
ans = s.findRedundantDirectedConnection(edges)
assert ans == expected

edges = [[1,2], [2,3], [3,4], [4,1], [1,5]]
expected = [4,1]
ans = s.findRedundantDirectedConnection(edges)
assert expected == ans

end = 1