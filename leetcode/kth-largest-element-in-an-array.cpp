// https://leetcode.com/problems/kth-largest-element-in-an-array/

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        multiset<int> mx;
        
        for (int n : nums) {
            mx.insert(n);
            if (mx.size() > k)
                mx.erase(mx.begin());
        }
        
        auto it = mx.rbegin();
        for (int i = 0; i < k-1; ++i)
            ++it;
        
        return *it;
    }
};
