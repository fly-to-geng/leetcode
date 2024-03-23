#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>

using namespace std;

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

int main()
{
    vector<string> tokens(5);
    tokens[0] = "20";
    tokens[1] = "12";
    tokens[2] = "+";
    tokens[3] = "2";
    tokens[4] = "*";
    int ans = evalRPN(tokens);
    printf("ans:%d\n", ans);

    return 0;
}