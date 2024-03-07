# [424. 逆波兰表达式求值](https://www.lintcode.com/problem/evaluate-reverse-polish-notation/description)

## 题目描述

求逆波兰表达式的值。
在逆波兰表达法中，其有效的运算符号包括 +, -, *, / 。每个运算对象可以是整数，也可以是另一个逆波兰计数表达。

样例 1:

    输入: ["2", "1", "+", "3", "*"] 
    输出: 9
    解释: ["2", "1", "+", "3", "*"] -> (2 + 1) * 3 -> 9

样例 2:

    输入: ["4", "13", "5", "/", "+"]
    输出: 6
    解释: ["4", "13", "5", "/", "+"] -> 4 + 13 / 5 -> 6

## 解题思路

求逆波兰表达式的值。在逆波兰表达法中，其有效的运算符号包括 +, -, *, / 。每个运算对象可以是整数，也可以是另一个逆波兰计数表达。

## AC 代码

```c
// 运算符只考虑了加减乘除
template<typename T>
T compute(T first, T second,string op){
    if(op == "+") return first + second;
    if(op == "-") return first - second;
    if(op == "*") return first * second;
    if(op == "/" && second != 0) return first / second;
    return -1000; // 说明输入的数据有问题
}
int evalRPN(vector<string> &tokens) {
    // write your code here
    stack<int > s;
    set<string> op = {"+","-","*","/"}; // 都是双目运算符，处理逻辑是相同的
    for(size_t i=0;i<tokens.size();i++){
        if(op.count(tokens[i]) > 0){
            int first=0,second=0;
            if(!s.empty()){ first = s.top() ; s.pop(); }
            if(!s.empty()){ second = s.top() ; s.pop(); }
            s.push(compute(second,first,tokens[i]));
        }else{
            s.push(stoi(tokens[i]));
        }
    }
    return s.top();
}
```