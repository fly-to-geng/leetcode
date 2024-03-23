from typing import List

class Solution:
    def sortItems(self, n: int, m: int, group: List[int], beforeItems: List[List[int]]) -> List[int]:
        def createGraphItem(groupIndex, group, beforeItems):
            """
            为每个分组单独创建一个图
            """
            items = {}
            for i in range(n):
                if group[i] == groupIndex:
                    items[i] = []
            for i in range(n):
                if group[i] == groupIndex:
                    for item in beforeItems[i]:
                        if group[item] == groupIndex:
                            items[item].append(i)
            return items

        def Topology(graph):
            """
            graph: [dict] 邻接表表示的图， keys 为点的集合， dic[key]是一个List
            return: 拓扑排序结果
            """
            def dfs(u):
                color[u] = 1
                for v in graph[u]:
                    if color[v] == 1:
                        return False
                    if color[v] == 0:
                        if not dfs(v):
                            return False
                color[u] = 2
                ans.insert(0, u)
                return True
            size = len(graph)
            color = {}
            for key in graph.keys():
                color[key] = 0
            ans = []
            for u in graph.keys():
                if color[u] == 0:
                    if not dfs(u):
                        return []
            return ans

        # -1 映射成 最大的组+1+当前索引
        groupMax = max(group)
        for i in range(n):
            if group[i] == -1:
                group[i] = i + groupMax + 1

        # 构造分组依赖关系的邻接表
        groupGraph = {}
        for i in range(n):
            if group[i] not in groupGraph:
                groupGraph[ group[i] ] = []
        for i in range(n):
            for item in beforeItems[i]:
                if group[item] != group[i]:
                    groupGraph[ group[item] ].append(group[i])

        # 获得拓扑排序
        orderedGroups = Topology(groupGraph)
        if not orderedGroups:
            return []

        # 对各个组内进行拓扑排序
        ans = []
        for groupIndex in orderedGroups:
            if groupIndex > groupMax:
                ans.append(groupIndex - groupMax - 1)
                continue
            graphItem = createGraphItem(groupIndex, group, beforeItems)
            tmp = Topology(graphItem)
            if not tmp:
                return []
            ans.extend(tmp)
        return ans

n = 30000
m = 13931
group = [2,0,-1,3,0]
beforeItems = [[2,1,3],[2,4],[],[],[]]

s = Solution()
ans = s.sortItems(n, m, group, beforeItems)
end = 10

# 超时， 未通过所有用例

        
            
        
