// https://leetcode.com/problems/search-in-rotated-sorted-array/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        
        int L = 0;
        int R = nums.size() - 1;
        
        while (L < R && nums[L] >= nums[R]) {
            int M = L + (R - L) / 2;
            if (nums[M] > nums[R]) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        
        vector<int>::iterator it;
        
        if (target <= nums.back()) {
            it = lower_bound(nums.begin()+L, nums.end(), target);
        } else {
            it = lower_bound(nums.begin(), nums.begin()+L, target);
        }
        
        return it != nums.end() && *it == target ? it - nums.begin() : -1;
    }
};
