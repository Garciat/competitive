// https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        sort(begin(nums), end(nums));
        
        int64_t ans = work(nums, nums[nums.size()/2]);
        
        if (nums.size() > 1 && nums.size()%2==0)
            ans = min(ans, work(nums, nums[nums.size()/2+1]));
        
        return ans;
    }
    
    int64_t work(vector<int>& ns, int64_t x) {
        int64_t ans = 0;
        for (int n : ns)
            ans += abs(x - n);
        return ans;
    }
};
