// https://leetcode.com/problems/shuffle-an-array/

class Solution {
    
    vector<int> orig, curr;
    
public:
    Solution(vector<int> nums) : orig(nums), curr(nums) {
        
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return orig;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        random_shuffle(begin(curr), end(curr));
        return curr;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */
