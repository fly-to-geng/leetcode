from typing import List

class Solution:
    def validateStackSequences(self, pushed: List[int], popped: List[int]) -> bool:
        stack = []
        start = 0
        for pop in popped:
            if start < len(pushed) and pushed[start] == pop:
                start += 1
            elif len(stack) > 0 and stack[-1] == pop:
                stack.pop()
            else:
                while (start < len(pushed) and pushed[start] != pop):
                    stack.append(pushed[start])
                    start += 1
                start += 1
        if len(stack) == 0:
            return True
        return False