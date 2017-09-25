// https://leetcode.com/problems/maximum-subarray/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int best = nums[0];
        int curr = nums[0];
        
        for (int i = 1; i < nums.size(); ++i) {
            curr = max(curr + nums[i], nums[i]);
            best = max(best, curr);
        }
        
        return best;
    }
};
