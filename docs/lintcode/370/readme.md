# [370. 将表达式转换为逆波兰表达式](https://www.lintcode.com/problem/convert-expression-to-reverse-polish-notation/description)

## 题目描述

给定一个字符串数组，它代表一个表达式，返回该表达式的逆波兰表达式。（去掉括号）

样例 1:

    输入: ["3", "-", "4", "+", "5"]
    输出: ["3", "4", "-", "5", "+"]
    解释: 3 - 4 + 5 = -1 + 5 = 4
        3 4 - 5 + = -1 5 + = 4
样例 2:

    输入: ["(", "5", "-", "6", ")", "*", "7"]
    输出: ["5","6","-","7","*"]
    解释: (5 - 6) * 7 = -1 * 7 = -7
        5 6 - 7 * = -1 7 * = -7

## 解题思路


## AC 代码

```c
bool isNumber(string &s){
    // 1. 空字符串不是数字
    if(s.empty()) return false;
    if(s.size() == 1 && s[0] == '-') return false;
    for(size_t i=0;i<s.length();i++){
        // 2. 如果第二个字符及以后的不是0--9，不是数字，直接返回false
        if( (i>0 && (s[i]<'0'||s[i]>'9')) ) return false;
        // 3. 如果第一个字符不是0--9，也不是-，则不是数字，直接返回false.
        if(i==0&&(s[i]!='-')&&(s[i]<'0'||s[i]>'9') ) return false;
    }
    return true;
}
vector<string> convertToRPN(vector<string> &expression) {
    // write your code here
    vector<string> ans;
    if(expression.empty()) return ans;

    // 操作符
    stack<string> s;
    // 操作符的优先级
    map<string,int> kv; 
    kv["+"] = 3; kv["-"] = 3; 
    kv["*"] = 4; kv["/"] = 4; 
    kv["("] = 2; kv[")"] = 6;
    for(size_t i=0;i<expression.size();i++){
        // 1. 如果是数字，直接输出
        if(isNumber(expression[i])){
            ans.push_back(expression[i]);
        }
        // 2. 如果是符号+,-,*,/,(,),需要按照优先级顺序处理
        else if(kv[expression[i]] >= 2 && kv[expression[i]] <= 6){
            // 2.1 如果栈为空，或者是左括号，直接入栈
            if(s.empty() || kv[expression[i]]==2 ){
                s.push(expression[i]);
            }
            // 2.2 如果遇到的是右括号，持续输出栈中的元素，直到遇到左括号为止
            else if(kv[expression[i]] == 6){
                while(!s.empty() && s.top() != "("){
                    ans.push_back(s.top()); s.pop();
                }
                if(!s.empty()) s.pop(); // 弹出左括号
            }
            // 如果是+,-,*,/，就要比较和当前栈顶元素的优先级了，如果比栈顶运算符的优先级低，可以直接入栈，
            // 如果高，需要弹出栈顶元素，直到栈顶的运算符低于当前的运算符或者栈为空为止
            else if(kv[expression[i]]==3 || kv[expression[i]]==4){
                 // 2.3 如果当前的运算符优先级高于栈顶的，直接入栈
                 if(kv[expression[i]] > kv[s.top()]){
                     s.push(expression[i]);
                 }else{
                     while(!s.empty() && kv[expression[i]] <= kv[s.top()]){
                         ans.push_back(s.top()); s.pop();
                     }
                     s.push(expression[i]);
                 }
            }
        }
    }
    // 把栈中的操作符输出
    while(!s.empty()){
        ans.push_back(s.top()); s.pop(); 
    } 
    return ans;
}
```