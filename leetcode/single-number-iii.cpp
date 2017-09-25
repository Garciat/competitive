// https://leetcode.com/problems/single-number-iii/

class Solution {
public:
    vector<int> singleNumber(vector<int>& xs) {
        auto k = 0;
        for (auto x : xs)
            k ^= x;
        auto r = k & -k;
        vector<int> ans = {0, 0};
        for (auto x : xs) {
            if (x & r) {
                ans[0] ^= x;
            } else {
                ans[1] ^= x;
            }
        }
        return ans;
    }
};
