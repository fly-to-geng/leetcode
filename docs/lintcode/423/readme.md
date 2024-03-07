# [423. 有效的括号序列](https://www.lintcode.com/problem/valid-parentheses/description)

## 题目描述

给定一个字符串所表示的括号序列，包含以下字符： '(', ')', '{', '}', '[' and ']'， 判定是否是有效的括号序列。
括号必须依照 "()" 顺序表示， "()[]{}" 是有效的括号，但 "([)]" 则是无效的括号。


样例
	样例 1：
	输入："([)]"
	输出：False
	样例 2：
	输入："()[]{}"
	输出：True

挑战
	O(n)的时间，n 为括号的个数。
	
## 解题思路

使用栈存储所有的左括号，一旦遇到右括号就与栈顶的元素比较，如果匹配，弹出栈顶元素，继续，如果不匹配，直接返回false.

## AC 代码

```c
class Solution {
public:
    /**
     * @param s: A string
     * @return: whether the string is a valid parentheses
     */
    bool isValidParentheses(string& s) {
        stack<char> cc;
        map<char,char> m;
        m['('] = ')';
        m['['] = ']';
        m['{'] = '}';
        for(int i=0;i<s.size();++i){
            if(s[i] == '(' || s[i] == '['|| s[i]=='{'){
                cc.push(s[i]);
            }
            if(s[i] == ')' || s[i] == ']' || s[i] == '}'){
                if (cc.empty()) return false;
                char tmp = cc.top();
                if(m[tmp] != s[i]){
                    return false;
                }
                cc.pop();
            }
        }
        if(cc.empty()) return true;
        return false;
    }
};
```