class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        currNum = 0
        count = 0
        for num in nums:
            if count == 0:
                count = 1
                currNum = num
            elif num == currNum:
                count += 1
            else:
                count -= 1
        return currNum