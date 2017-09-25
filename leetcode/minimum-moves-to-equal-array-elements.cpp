// https://leetcode.com/problems/minimum-moves-to-equal-array-elements/

class Solution {
public:
    int minMoves(vector<int>& nums) {
        long long minx = 1LL + INT_MAX;
        long long s = 0LL;
        for (int x : nums) {
            s += x;
            minx = min((long long)x, minx);
        }
        return s - minx*nums.size();
    }
};
