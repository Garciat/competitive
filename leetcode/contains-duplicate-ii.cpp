// https://leetcode.com/problems/contains-duplicate-ii/

/*

algo 1:
    
    O(k * n) space
    O(n) time

algo 2:
    O(1) space
    O(k * n) time

algo 3:
    O(k) space
    O(n) time

fail:
    
    underflow:
        nums.size() - d

*/

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> m;
        
        for (int i = 0; i < min((int)nums.size(), k+1); ++i) {
            if (!m.insert(nums[i]).second) {
                return true;
            }
        }
        
        for (int i = k+1; i < nums.size(); ++i) {
            m.erase(nums[i - k - 1]);
            
            if (!m.insert(nums[i]).second) {
                return true;
            }
        }
        
        return false;
    }
};
