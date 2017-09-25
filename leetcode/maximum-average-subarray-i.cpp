// https://leetcode.com/problems/maximum-average-subarray-i/

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double avg = 0.0;
        for (int i = 0; i < k; ++i) {
            avg += nums[i] / (double)k;
        }
        double ans = avg;
        for (int i = k; i < nums.size(); ++i) {
            avg -= nums[i-k] / (double)k;
            avg += nums[i] / (double)k;
            ans = max(ans, avg);
        }
        return ans;
    }
};
