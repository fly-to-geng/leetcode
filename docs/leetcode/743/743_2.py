
from typing import List

import heapq
import numpy as np

INF = float('inf')
class Solution:
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

    def networkDelayTime(self, times: List[List[int]], N: int, K: int) -> int:
        times = [[u - 1, v - 1, w] for u, v, w in times]
        distance = self.BellmanFord(times, K - 1, N)
        ans = max(distance)
        if ans == INF:
            return -1
        return int(ans)

s = Solution()
times = [[2,1,1],[2,3,1],[3,4,1]]
N = 4
K = 2
expected = 2

times = [[1,2,1],[2,1,3]]
N = 2
K = 2
expected = 3

ans = s.networkDelayTime(times, N, K)
assert expected == ans

end = 10