// https://leetcode.com/problems/longest-harmonious-subsequence/


class Solution {
    
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> m;
        for (auto n : nums)
            m[n] += 1;
        int ans = 0;
        for (auto p : m) {
            auto q = m.find(p.first + 1);
            if (q == m.end()) continue;
            ans = max(ans, p.second + q->second);
        }
        return ans;
    }
};

