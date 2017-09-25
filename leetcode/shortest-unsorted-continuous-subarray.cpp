// https://leetcode.com/problems/shortest-unsorted-continuous-subarray/

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.empty()) return 0;
        int i = INT_MAX;
        int j = INT_MIN;
        
        for (int k = 0; k < nums.size(); ++k) {
            int m = k;
            while (m+1 < nums.size()) {
                if (nums[k] <= nums[m+1]) {
                    break;
                }
                m += 1;
            }
            if (m != k) {
                i = min(i, k);
                j = max(j, m);
                k = m;
            }
        }
        
        for (int k = nums.size()-1; k >= 0; --k) {
            int m = k;
            while (m-1 >= 0) {
                if (nums[k] >= nums[m-1]) {
                    break;
                }
                m -= 1;
            }
            if (m != k) {
                i = min(i, m);
                j = max(j, k);
                k = m;
            }
        }
        
        return i == INT_MAX ? 0 : j - i + 1;
    }
};
