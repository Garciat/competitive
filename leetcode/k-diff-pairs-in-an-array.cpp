// https://leetcode.com/problems/k-diff-pairs-in-an-array/

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if (k < 0) return 0;
        int ans = 0;
        unordered_set<int> m;
        unordered_set<int> f;
        for (int n : nums) {
            if (m.find(n) != m.end()) {
                if (f.find(n) != f.end())
                    continue;
                if (k == 0)
                    ans += 1;
                f.insert(n);
                continue;
            }
            if (m.find(n - k) != m.end())
                ans += 1;
            if (m.find(n + k) != m.end())
                ans += 1;
            m.insert(n);
        }
        return ans;
    }
};
