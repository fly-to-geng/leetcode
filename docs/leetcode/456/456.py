
from typing import List

class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        if len(nums) < 3:
            return False

        # 计算前缀最小值
        mins = [0] * len(nums)
        mins[0] = nums[0]
        for i in range(1, len(nums)):
            mins[i] = min(mins[i-1], nums[i])

        stack = []
        for i in reversed(range(0, len(nums))):
            if nums[i] <= mins[i]:
                continue
            while (len(stack) > 0 and stack[-1] <= mins[i]):
                stack.pop()
            if (len(stack) > 0 and stack[-1] < nums[i]):
                return True
            stack.append(nums[i])
        
        return False

nums = [1,4,3,2]
s = Solution()
ans = s.find132pattern(nums)
print(ans)