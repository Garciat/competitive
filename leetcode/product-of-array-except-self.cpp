// https://leetcode.com/problems/product-of-array-except-self/

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> ans(nums.size(), 1);
        
        work(ans, nums, 0, nums.size());
        
        return ans;
    }
    
    int work(vector<int>& ans, vector<int>& nums, int i, int j) {
        if (i >= j) return 1;
        
        if (j - i == 1) return nums[i];
        
        int k = (i + j) / 2;
        
        int p = work(ans, nums, i, k);
        int q = work(ans, nums, k, j);
        
        for (int r = i; r < k; ++r) {
            ans[r] *= q;
        }
        
        for (int r = k; r < j; ++r) {
            ans[r] *= p;
        }
        
        return p * q;
    }
};
