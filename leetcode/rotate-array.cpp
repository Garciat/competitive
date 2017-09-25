// https://leetcode.com/problems/rotate-array/

/*
if k >= n: k %= n ?

simple algorithm:
  split list at k into two lists (a, b)
  concatenate lists in reverse (b, a)



*/

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        std::reverse(nums.begin(), nums.end());
        std::reverse(nums.begin(), nums.begin() + k);
        std::reverse(nums.begin() + k, nums.end());
    }
};
