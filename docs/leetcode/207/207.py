from typing import List

class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        def dfs(G, i, color):
            color[i] = 1
            for j in range(len(G)):
                if i != j and G[i][j] != 0:
                    if color[j] == 1:
                        return True
                    if color[j] == 0:
                        ans = dfs(G, j, color)
                        if ans == True:
                            return True
            color[i] = 2
            return False
            
        def isCycle(G):
            color = [0] * len(G)
            for i in range(len(G)):
                if color[i] == 0:
                    ans = dfs(G, i, color)
                    if ans == True:
                        return True
            return False
        G = [ [0 for _ in range(numCourses)] for _ in range(numCourses)]
        for u, v in prerequisites:
            G[u][v] = 1
        ans = isCycle(G)
        return not ans

s = Solution()

numCourses = 3
pre =  [[0,2],[1,2],[2,0]]
ans = s.canFinish(numCourses, pre)
expected = False
assert expected == ans
end = 10