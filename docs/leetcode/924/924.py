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
    def get_count(self, i):
        """
        获取节点 i 所在的组有多少个元素
        """
        if i < 0:
            return 0
        cc = 0
        parent = self.parent(i)
        for ele in self.array:
            if parent == self.parent(ele):
                cc += 1
        return cc
    def minMalwareSpread(self, graph: List[List[int]], initial: List[int]) -> int:
        n = len(graph)
        if n == 0: return -1

        # 分成几组点
        self.create(n)
        for i in range(n):
            for j in range(n):
                if i != j and graph[i][j] == 1:
                    self.merge(i, j)

        # 对于每个污染的点，查找是否有其他的点与其在同一个组，如果在，移除这个组的污染点没有意义
        # 如果不和其他污染点在一组，可以移除它，记录获益的点数，只有当下一个满足条件的污染点获益的点数大于它时，才更新
        # 如果遍历完成没有任何结果，说明移除任何一个点都没有任何作用，返回一个最小的点即可
        ans = -1
        max_count = 0
        initial = sorted(initial)
        flag = [0] * len(initial) # 是否跳过
        for i in range(len(initial)):
            if flag[i]:
                continue
            
            single = True
            if i < len(initial) - 1:
                for j in range(i + 1, len(initial)):
                    if self.parent(initial[i]) == self.parent(initial[j]):
                        flag[i] = 1
                        flag[j] = 1
                        single = False
            if single:
                count = self.get_count(initial[i])
                if count > max_count:
                    ans = initial[i]
                    max_count = count
        
        # 如果ans 根本未曾更新过，说明所有点都不是孤立的
        if ans == -1:
            ans = min(initial)
        return ans


graph = [[1,0,0,0],[0,1,0,0],[0,0,1,1],[0,0,1,1]]
initial = [3, 1]
expected = 1
s = Solution()
ans = s.minMalwareSpread(graph, initial)

graph = [[1,1,0],[1,1,0],[0,0,1]]
initial = [0,1,2]
expected = 2
ans = s.minMalwareSpread(graph, initial)
assert ans == expected

graph = [[1,0,0,0,1,0,0,0,0,0],[0,1,1,0,0,0,0,0,0,0],[0,1,1,0,0,1,0,0,0,0],[0,0,0,1,0,0,0,0,0,0],[1,0,0,0,1,0,0,0,0,0],[0,0,1,0,0,1,0,0,0,0],[0,0,0,0,0,0,1,0,0,1],[0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,0,1,0],[0,0,0,0,0,0,1,0,0,1]]
initial = [1,3,0]
expected = 1
ans = s.minMalwareSpread(graph, initial)
assert ans == expected


graph = [[1,1,0,0,0,0,0,0,0,0],
         [1,1,1,1,0,0,0,0,0,0],
         [0,1,1,0,0,1,0,0,0,0],
         [0,1,0,1,0,0,0,1,0,1],
         [0,0,0,0,1,0,1,0,0,0],
         [0,0,1,0,0,1,0,0,0,1],
         [0,0,0,0,1,0,1,0,1,0],
         [0,0,0,1,0,0,0,1,0,0],
         [0,0,0,0,0,0,1,0,1,0],
         [0,0,0,1,0,1,0,0,0,1]]
initial = [3,1,9]
expected = 1
ans = s.minMalwareSpread(graph, initial)
assert ans == expected

end = 10           
        