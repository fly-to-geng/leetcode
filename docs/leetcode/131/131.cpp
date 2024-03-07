#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <deque>

using namespace std; 

class Solution {
public:
    bool isHuiWen(string &s, int begin, int end) {
        while (begin < end) {
            if (s[begin] != s[end]) {
                return false;
            }
            begin++;
            end--;
        }
        return true;
    }
    void dfs(int begin, int end, string &s, vector<string> &line, vector<vector<string>> &ans) {
        if (end == s.size()) {
            // 满足回文条件，begin 一定等于 end
            if (begin == end) {
                ans.push_back(line);
            }
            return;
        }

        // 如果是回文，就从这里切割
        if (isHuiWen(s, begin, end)) {
            line.push_back(s.substr(begin, end - begin + 1));
            dfs(end+1, end+1, s, line, ans);
            line.pop_back();
        }

        // 是不是回文，都可以不切割，继续向下搜索
        dfs(begin, end+1, s, line, ans);
        return;
    }
    
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> line;

        dfs(0, 0, s, line, ans);

        return ans;
    }
};

int main()
{
    Solution *s = new Solution();
    auto ans = s->partition("aab");
    return 0;
}