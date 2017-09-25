// https://leetcode.com/problems/4sum-ii/

class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> m, n;
        
        for (auto x : A)
            for (auto y : B)
                m[x + y] += 1;
        
        for (auto x : C)
            for (auto y : D)
                n[x + y] += 1;
        
        int ans = 0;
        
        for (auto p : m) {
            auto q = n.find(-p.first);
            if (q == n.end()) continue;
            ans += p.second * q->second;
        }
        
        return ans;
    }
};
