# -*- coding:utf-8 -*-
from typing import List

class Solution:
    def op(self, num1, num2, token):
        if token == "+":
            return num1 + num2
        if token == "-":
            return num1 - num2
        if token == "*":
            return num1 * num2
        if token == "/":
            return int(num1 / num2) # 先求除法再取整， int与C语言处理一致

    def evalRPN(self, tokens: List[str]) -> int:
        stack = []
        for token in tokens:
            if token in ["+", "-", "*", "/"]:
                number1 = stack.pop()
                number2 = stack.pop()
                number3 = self.op(number2, number1, token)
                stack.append(number3)
            else:
                stack.append(int(token))
        if len(stack) != 1:
            print(stack)
        else:
            return stack[0]


s = Solution()
ans = s.evalRPN(["10","6","9","3","+","-11","*","/","*","17","+","5","+"])
print(ans)