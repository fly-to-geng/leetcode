from typing import List
from functools import cmp_to_key

class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        def compare(a, b):
            return b[1] - a[1]
        # 1. 统计出现次数
        dic = {}
        for task in tasks:
            if task not in dic:
                dic[task] = 1
            else:
                dic[task] += 1
        # 2. 按照出现次数从大到小排序
        listcount = list(dic.items())
        listcount = sorted(listcount, key=cmp_to_key(compare))
        # 3. 取出最大值
        maxcount = listcount[0][1]
        space = (maxcount - 1) * n # 空位置数量
        ans = space + maxcount # 当前消耗时间
        
        # 遍历剩下的，如果有空余的空间，就减少剩余空间，如果没有，就添加
        for i in range(1, len(listcount)):
            if listcount[i][1] == maxcount:
                ans += 1
                if space >= maxcount - 1:
                    space -= (maxcount - 1)
                else:
                    return len(tasks)
            else:
                if space >= listcount[i][1]:
                    space -= listcount[i][1]
                else:
                    return len(tasks)
        return ans



tasks = ["A","A","A","B","B","B"]
n = 2
s = Solution()
ans = s.leastInterval(tasks, n)
end = 10