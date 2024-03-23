#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int minAddToMakeValid(string S) {
        int ans = 0;
        stack<char> st;
        for (int i = 0; i < S.size(); i++) {
            if (S[i] == '(') {
                st.push(S[i]);
            } else {
                if (!st.empty()) {
                    st.pop();
                } else {
                    ans++;
                }
            }
        }
        ans += st.size();
        return ans;
    }
};

int main()
{
    string str = "(())))";
    Solution *s = new Solution();
    int ans = s->minAddToMakeValid(str);
    printf("%d\n", ans);
    return 0;
}