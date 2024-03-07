#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <deque>

using namespace std; 

class Solution {
public:
    void dfs(int start, int target, vector<int>& candidates, vector<int> &line, vector<vector<int>> &ans) {
        if (target == 0) {
            ans.push_back(line);
            return;
        }
        if (start == candidates.size()) {
            return;
        }
        for (int i = start; i < candidates.size(); i++) {
            if (i > start && candidates[i] == candidates[i-1]) {
                continue;
            }
            if (candidates[i] > target) {
                break;
            }
            line.push_back(candidates[i]);
            dfs(i + 1, target - candidates[i], candidates, line, ans);
            line.pop_back();
        }
        return;
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;

        if (candidates.empty()) {
            return ans;
        }

        sort(candidates.begin(), candidates.end());

        vector<int> line;
        for (int i = 0; i < candidates.size(); i++) {
            if (i > 0 && candidates[i] == candidates[i-1]) {
                continue;
            }
            if (candidates[i] > target) {
                break;
            }
            line.push_back(candidates[i]);
            dfs(i + 1, target - candidates[i], candidates, line, ans);
            line.pop_back();
        }

        return ans;
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> candidates = {10,1,2,7,6,1,5};
    int target = 8;
    auto ans = s->combinationSum2(candidates, target);
    return 0;
}