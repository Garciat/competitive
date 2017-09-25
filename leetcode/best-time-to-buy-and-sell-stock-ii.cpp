// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }
        
        int ans = 0;
        int b = prices[0];
        int k = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] < prices[i-1]) {
                ans += k;
                b = prices[i];
                k = 0;
            } else {
                k = max(k, prices[i] - b);
            }
        }
        ans += k;
        return ans;
    }
};
