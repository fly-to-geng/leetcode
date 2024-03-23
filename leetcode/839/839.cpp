#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int size; // 并查集中有几个集合
    vector<int> create(int n) {
        vector<int> array(n);
        for (int i = 0; i < n; i++) {
            array[i] = i;
        }
        size = n;
        return array;
    }
    int parent(vector<int> &array, int i) {
        if (array[i] == i) {
            return i;
        }
        array[i] = parent(array, array[i]);
        return array[i];
    }
    void merge(vector<int> &array, int i, int j) {
        int pi = parent(array, i);
        int pj = parent(array, j);
        if (pi != pj) {
            array[pj] = pi;
            size -= 1;
        }
    }
    bool similar(string &a, string &b) {
        if (a.size() != b.size()) {
            return false;
        }
        int diff = 0;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                diff += 1;
            }
            if (diff > 2) {
                return false;
            }
        }
        if (diff == 0 || diff == 2) {
            return true;
        }
        return false;
    }
    int numSimilarGroups(vector<string>& A) {
        if (A.size() == 0) {
            return 0;
        }
        vector<int> array = create(A.size());
        for (int i = 0; i < A.size() - 1; i++) {
            for (int j = i + 1; j < A.size(); j++) {
                if (similar(A[i], A[j])) {
                    merge(array, i, j);
                }
            }
        }
        return size;
    }
};

int main()
{
    Solution *s = new Solution();

    vector<string> A = {"tars","rats","arts","star"};
    int ans = s->numSimilarGroups(A);
    return 0;
}

