#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
        int start = 0;
        for (size_t i = 0; i < popped.size(); i++) {
            if (start < pushed.size() && popped[i] == pushed[start]) {
                start++;
            } else if (!s.empty() && s.top() == popped[i]) {
                s.pop();
            } else {
                while (start < pushed.size() && pushed[start] != popped[i]) {
                    s.push(pushed[start++]);
                }
                start++;
            }
        }
        if (s.empty()) {
            return true;
        }

        return false;
    }
};

int main()
{
    vector<int> pushed = {1,2,3,4,5};
    vector<int> poped = {4,5,3,2,1};
    Solution *s = new Solution();
    bool ans = s->validateStackSequences(pushed, poped);
    return 0;
}