from typing import List

class Solution:
    def create(self, n):
        self.array = [i for i in range(n)]
        self.n = n
    
    def parent(self, i):
        """ 返回i的根节点
        array[i] 中存放 i的根， 如果 array[i] == i, 说明这个点是根节点
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
    def numIslands(self, grid: List[List[str]]) -> int:
        zero_count = 0
        m = len(grid)
        if m == 0: return 0
        n = len(grid[0])
        if n == 0: return 0
        self.create(m * n)
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '0':
                    zero_count += 1
                    continue
                if i == 0 and j > 0:
                    if grid[i][j] == grid[i][j-1]:
                        self.merge(i * n + j, i * n + j - 1)
                if i > 0 and j == 0:
                    if grid[i][j] == grid[i-1][j]:
                        self.merge(i * n + j, (i - 1) * n + j)
                if  i > 0 and j > 0:
                    if grid[i][j] == grid[i-1][j]:
                        self.merge(i * n + j, (i - 1) * n + j)
                    if grid[i][j] == grid[i][j-1]:
                        self.merge(i * n + j, i * n + j - 1)
        count = self.count()
        return count - zero_count

s = Solution()
grid = [["1","1","1","1","0"],
        ["1","1","0","1","0"],
        ["1","1","0","0","0"],
        ["0","0","0","0","0"]]
expected = 1
ans = s.numIslands(grid)
assert ans == expected


grid = [["1","1","1","1","0"],
        ["1","1","0","1","0"],
        ["0","0","0","0","1"],
        ["1","1","1","0","0"]]
expected = 3
ans = s.numIslands(grid)
assert ans == expected


end = 10