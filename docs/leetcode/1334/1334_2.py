from typing import List
import heapq
import numpy as np

INF = float("inf")

class Solution:
    def dijkstra(self, g, s):
        """
        dijkstra 算法实现
        g : 临界矩阵表示的图, g[i][i] = 0, g[i][j] = INF if i与j之间没有边
        s : 源点
        返回值是一个一维数组，表示源点到各个点的最短距离
        """
        n = len(g) # 点个数

        # 所有节点加入集合q, 用与源点s的距离作为key建立小顶堆
        q = []
        for point in range(n):
            if (g[s][point] != INF):
                heapq.heappush(q, [g[s][point], point])
            else:
                heapq.heappush(q, [INF, point]) # [dis, point] 表示 s->point 最短距离是 dis

        distance = [INF for _ in range(n)]
        distance[s] = 0
        while len(q) > 0:
            dis, u = heapq.heappop(q)
            distance[u] = dis
            for i in range(len(q)):
                if q[i][0] > dis + g[u][ q[i][1] ]:
                    q[i][0] = dis + g[u][ q[i][1] ]
            heapq.heapify(q) # 调整之后重新建立堆
        return distance
    def BellmanFord(self, edges, s, N):
        """
        BellmanFord 算法实现
        edges: (u, v, w) 的集合，表示边 u-->v 的权重为 w
        s : 源点
        返回值是一个一维数组，表示源点到各个点的最短距离
        N: 图中点的个数
        """
        distance = np.zeros(N)
        distance.fill(INF)
        distance[s] = 0
        for _ in range(N):
            distance_tmp = np.copy(distance)
            for u, v, w in edges:
                if distance[v] > distance[u] + w:
                    distance[v] = distance[u] + w
            if np.array_equal(distance, distance_tmp):
                break
        for u, v, w in edges:
            if distance[v] > distance[u] + w:
                print("存在负权回路")
        return distance
    def Johnson(self, g):
        """
        g: 邻接矩阵表示的图，图中值表示权重，无边连接用INF，自身用0
        """
        n = len(g)
        edges = []
        for i in range(n):
            for j in range(n):
                if g[i][j] != 0 and g[i][j] != INF:
                    edges.append( [i, j, g[i][j]] )
        for i in range(n):
            edges.append([n, i, 0]) # 超级源点到任意其他点的距离都设置为0
        
        # 求超级源点到其他各点的最短路径
        distance = self.BellmanFord(edges, n, n + 1)

        # 用求得的最短路径更新边的权值
        for i in range(n):
            for j in range(n):
                if g[i][j] != 0 and g[i][j] != INF:
                    g[i][j] = g[i][j] + distance[i] - distance[j]

        # 使用dijkstra算法求解
        matrix = []
        for i in range(n):
            distance = self.dijkstra(g, i)
            matrix.append(distance)

        return matrix

    def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        g = [ [INF for _ in range(n)] for _ in range(n)]
        for u, v, w in edges:
            g[u][v] = w
            g[v][u] = w
        g = self.Johnson(g)
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