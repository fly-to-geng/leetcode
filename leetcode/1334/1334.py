
from typing import List
INF = float("inf")

class Solution:    
    def FloydWarshall(self, g):
        """
        g : 邻接矩阵表示的图，值表示权重，无边连接用INF表示，自身连接用0表示
        返回一个矩阵，表示每个点到每个点的最短距离
        """
        n = len(g)
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    if g[i][j] > g[i][k] + g[k][j]:
                        g[i][j] = g[i][k] + g[k][j]
        return g

    def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        g = [ [INF for _ in range(n)] for _ in range(n)]
        for u, v, w in edges:
            g[u][v] = w
            g[v][u] = w
        g = self.FloydWarshall(g)
        ans = INF
        point = -1
        for i in range(n):
            currAns = 0
            for j in range(n):
                if i != j and g[i][j] <= distanceThreshold:
                    currAns += 1
            if currAns <= ans:
                ans = currAns
                point = i
        return point

s = Solution()

# 用例1
edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]]
n = 4
distanceThreshold = 4
expected = 3

ans = s.findTheCity(n, edges, distanceThreshold)
assert ans == expected

# 用例2
edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]]
n = 5
distanceThreshold = 2
expected = 0

ans = s.findTheCity(n, edges, distanceThreshold)
assert ans == expected

end = 10
