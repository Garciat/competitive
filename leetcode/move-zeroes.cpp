// https://leetcode.com/problems/move-zeroes/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        stable_sort(begin(nums), end(nums), [](int x, int y) { return y == 0; });
    }
};
