// https://leetcode.com/problems/longest-continuous-increasing-subsequence/

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int ans = 0;
        int cur = 1;
        
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i-1] < nums[i]) {
                cur += 1;
            } else {
                ans = max(ans, cur);
                cur = 1;
            }
        }
        
        return max(ans, cur);
    }
};
