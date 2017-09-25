// https://leetcode.com/problems/max-consecutive-ones/

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        int a = 0;
        int m = nums[0] == 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i-1] && nums[i] == 1) {
                m += 1;
            } else {
                a = max(a, m);
                m = nums[i] == 1;
            }
        }
        a = max(a, m);
        return a;
    }
};
