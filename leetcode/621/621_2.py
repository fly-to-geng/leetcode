from typing import List

class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        # 1. 统计出现次数
        dic = {}
        for task in tasks:
            if task not in dic:
                dic[task] = 1
            else:
                dic[task] += 1
        maxv = max(dic.values())
        p = 0
        for key, value in dic.items():
            if value == maxv:
                p += 1

        ans = (maxv - 1) * (n + 1) + p
        ans = max(ans, len(tasks))
        return ans