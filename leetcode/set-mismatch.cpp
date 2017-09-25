// https://leetcode.com/problems/set-mismatch/

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        for (;;) {
            int n = 0;
            for (int i = 0; i < nums.size(); ++i) {
                if (nums[i] == i+1) continue;
                swap(nums[i], nums[nums[i]-1]);
                n += 1;
            }
            if (n == 1) break;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i+1)
                return {nums[i], i+1};
        }
        return {};
    }
};
