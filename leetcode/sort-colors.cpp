// https://leetcode.com/problems/sort-colors/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        if (nums.empty())
            return;
        
        int i = 0;
        int j = 0;
        
        for (int k = 0; k < nums.size(); ++k) {
            int v = nums[k];
            nums[k] = 2;
            if (v < 2) {
                nums[j] = 1;
                j += 1;
            }
            if (v == 0) {
                nums[i] = 0;
                i += 1;
            }
        }
    }
};
