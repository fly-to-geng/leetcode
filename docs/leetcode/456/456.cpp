#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        if (nums.size() < 3) return false;

        vector<int> mins(nums.size(), 0);
        
        mins[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            mins[i] = min(mins[i-1], nums[i]);
        }

        stack<int> s;
        for (int i = nums.size() - 1; i >= 0; i--) {
            // 前面没有更小的数字，下一轮
            if (nums[i] <= mins[i]) continue;
            // 弹出小于等于mins[i]的
            while (!s.empty() && s.top() <= mins[i]) s.pop();
            // 找到ak就返回
            if (!s.empty() && s.top() < nums[i]) return true;
            // 否则就入栈，继续下一轮
            s.push(nums[i]);
        }

        return false;
    }
};

int main()
{
    vector<int> nums = {1,3,4,2};
    Solution *s = new Solution();
    bool ans = s->find132pattern(nums);
    return 0;
}