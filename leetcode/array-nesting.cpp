// https://leetcode.com/problems/array-nesting/

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == -1) continue;
            ans = max(ans, work(nums, i));
        }
        return ans;
    }
    
    int work(vector<int>& nums, int i, int n=0) {
        int next = nums[i];
        if (next == -1) {
            return n;
        } else {
            nums[i] = -1;
            return work(nums, next, n+1);
        }
    }
};
