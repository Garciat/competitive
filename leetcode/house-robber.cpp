// https://leetcode.com/problems/house-robber/

/*



*/

class Solution {
public:
    int rob(vector<int>& nums) {
        memset(memo, -1, sizeof memo);
        return solve(nums, 0);
    }
    
    int memo[1000000];
    
    int solve(vector<int> &nums, int i) {
        if (i >= nums.size()) return 0;
        
        if (memo[i] != -1) return memo[i];
        
        return memo[i] = std::max(nums[i] + solve(nums, i + 2), solve(nums, i + 1));
    }
};
