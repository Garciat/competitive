// https://leetcode.com/problems/contains-duplicate/

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> z;
        for (int x : nums) {
            if (!z.insert(x).second) return true;
        }
        return false;
    }
};
