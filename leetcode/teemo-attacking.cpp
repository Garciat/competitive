// https://leetcode.com/problems/teemo-attacking/

class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (timeSeries.empty()) return 0;
        int ans = 0;
        for (int i = 1; i < timeSeries.size(); ++i) {
            ans += min(timeSeries[i] - timeSeries[i-1], duration);
        }
        ans += duration;
        return ans;
    }
};
