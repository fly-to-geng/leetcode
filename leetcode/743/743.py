
from typing import List

import heapq

INF = float('inf')

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
                heapq.heappush(q, [INF, point])

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
    def networkDelayTime(self, times: List[List[int]], N: int, K: int) -> int:
        g = [ [INF for _ in range(N)] for _ in range(N)]
        for u, v, w in times:
            g[u - 1][v - 1] = w
        for i in range(N):
            g[i][i] = 0
        distance = self.dijkstra(g, K-1)
        ans = max(distance)
        if ans == INF:
            return -1
        return ans

s = Solution()
times = [[2,1,1],[2,3,1],[3,4,1]]
N = 4
K = 2
expected = 2

ans = s.networkDelayTime(times, N, K)
assert expected == ans

end = 10