// https://leetcode.com/problems/relative-ranks/

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
        vector<string> ans(nums.size(), "");
        map<int, int> m;
        for (int i = 0; i < nums.size(); ++i) {
            m[nums[i]] = i;
        }
        int k = 1;
        for (auto it = m.rbegin(); it != m.rend(); ++k, ++it) {
            string &s = ans[it->second];
            if (k == 1)
                s = "Gold Medal";
            else if (k == 2)
                s = "Silver Medal";
            else if (k == 3)
                s = "Bronze Medal";
            else
                s = to_string(k);
        }
        return ans;
    }
};
