#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <deque>

using namespace std; 


class Solution {
public:
    void dfs(int start, int target, vector<int> &line, vector<vector<int>> &ans, vector<int>& candidates) {
        if (target == 0) {
            ans.push_back(line);
            return;
        }

        for (int i = start; i < candidates.size(); i++) {
            if (candidates[i] > target) {
                break;
            }
            line.push_back(candidates[i]);
            dfs(i, target - candidates[i], line, ans, candidates);
            line.pop_back();
        }
        return;
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        if (candidates.size() == 0) {
            return ans;
        }

        vector<int> line;
        sort(candidates.begin(), candidates.end());
        dfs(0, target, line, ans, candidates);

        return ans;

    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> can = {2,3,6,7};
    int target = 7;
    auto ans = s->combinationSum(can, target);
    return 0;
}