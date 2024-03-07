#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> t9 = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

    void dfs(int start, string &digits, string &line, vector<string> &ans) {
        if (start == digits.size()) {
            ans.push_back(line);
            return;
        }
        string curr = t9[ digits[start] - '0' - 2];
        for (int i = 0; i < curr.size(); i++) {
            line.push_back(curr[i]);
            dfs(start + 1, digits, line, ans);
            line.pop_back();
        }
        return;
    }

    vector<string> letterCombinations(string digits) {
        vector<string> ans;

        if (digits.empty()) {
            return ans;
        }

        string line;
        
        dfs(0, digits, line, ans);

        return ans;
    }
};

int main()
{
    string nums = "23";
    Solution *s = new Solution();
    auto ans = s->letterCombinations(nums);
    for (auto a : ans) {
        printf("%s, ", a);
    }
    return 0;
}