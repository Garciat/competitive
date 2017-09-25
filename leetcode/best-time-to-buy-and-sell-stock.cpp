// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/



class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int64_t min_seen = INT_MAX;
        int64_t max_seen = INT_MIN;
        
        int64_t ans = 0;
        
        for (int p : prices) {
            if (p > max_seen) {
                max_seen = p;
            }
            if (p < min_seen) {
                min_seen = p;
                max_seen = INT_MIN;
            }
            
            ans = max(ans, max_seen - min_seen);
        }
        
        if (ans > INT_MAX) return 0;
        
        return ans;
    }
};
