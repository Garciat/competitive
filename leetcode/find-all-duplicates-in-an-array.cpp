// https://leetcode.com/problems/find-all-duplicates-in-an-array/

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        for (;;) {
            int swaps = 0;
            for (int i = 0; i < nums.size(); ++i) {
                swap(nums[i], nums[nums[i]-1]);
                swaps += nums[i] != nums[nums[i]-1];
            }
            if (swaps == 0)
                break;
        }
        vector<int> ans;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i+1) {
                ans.push_back(nums[i]);
            }
        }
        return ans;
    }
};
