from typing import List

class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
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
        def Topology(G, i, color):
            color[i] = 1
            #outlist.append(i)
            for point, value in enumerate(G[i]):
                if value != 0 and color[point] == 0:
                    Topology(G, point, color)
            color[i] = 2
            outlist.insert(0, i) # 访问完之后逆序输出

        G = [ [0 for _ in range(numCourses)] for _ in range(numCourses)]
        for u, v in prerequisites:
            G[v][u] = 1
        cycle = isCycle(G)
        if cycle:
            return []
        outlist = []
        color = [0 for _ in range(len(G))]
        for i in range(len(G)):
            if color[i] == 0:
                Topology(G, i, color)
        
        return outlist

s = Solution()

numCourses = 2
pre =  [[1,0]]
ans = s.findOrder(numCourses, pre)
expected = [0,1,2,3]
assert expected == ans
end = 10