// https://leetcode.com/problems/first-missing-positive/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if (nums.empty()) return 1;
        
        for (int i = 0; i < nums.size(); ++i) {
            work(nums, i, nums[i]);
        }
        
        for (int i = 0; i < nums.size(); ++i) {
            if (i + 1 != nums[i]) {
                return i + 1;
            }
        }
        
        return nums.size() + 1;
    }
    
    void work(vector<int>& nums, int i, int x) {
        if (i < 0 || i >= nums.size()) return;
        if (nums[i] == i + 1) return;
        int j = nums[i] - 1;
        nums[i] = x;
        work(nums, j, j+1);
    }
};
