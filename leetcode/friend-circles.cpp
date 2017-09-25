// https://leetcode.com/problems/friend-circles/

class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int ans = 0;
        array<bool, 200> seen;
        fill(begin(seen), end(seen), false);
        for (int i = 0; i < M.size(); ++i) {
            if (seen[i])
                continue;
            work(M, seen, i);
            ans += 1;
        }
        return ans;
    }
    
    void work(vector<vector<int>>& M, array<bool, 200> &seen, int i) {
        if (seen[i])
            return;
        seen[i] = true;
        for (int j = 0; j < M.size(); ++j) {
            if (M[i][j] || M[j][i]) {
                work(M, seen, j);
            }
        }
    }
};
