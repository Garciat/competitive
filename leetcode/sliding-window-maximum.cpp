// https://leetcode.com/problems/sliding-window-maximum/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (nums.empty()) return {};
        
        multiset<int, greater<int>> xs;
        
        for (int i = 0; i < k; ++i)
            xs.insert(nums[i]);
        
        vector<int> ans;
        ans.push_back(*xs.begin());
        
        for (int i = k; i < nums.size(); ++i) {
            xs.erase(xs.find(nums[i - k]));
            xs.insert(nums[i]);
            ans.push_back(*xs.begin());
        }
        
        return ans;
    }
};
