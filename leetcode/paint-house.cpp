// https://leetcode.com/problems/paint-house/


class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (costs.empty()) return 0;
        for (int i = 1; i < costs.size(); ++i) {
            for (int j = 0; j < 3; ++j) {
                costs[i][j] += min(costs[i-1][(j+1)%3], costs[i-1][(j+2)%3]);
            }
        }
        auto b = costs.back();
        return min(b[0], min(b[1], b[2]));
    }
};

