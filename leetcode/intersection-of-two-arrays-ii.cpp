// https://leetcode.com/problems/intersection-of-two-arrays-ii/

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, pair<int, int>> c;
        
        for (auto x : nums1) {
            c[x].first += 1;
        }
        
        for (auto x : nums2) {
            c[x].second += 1;
        }
        
        vector<int> ans;
        
        for (auto p : c) {
            for (int i = 0; i < min(p.second.first, p.second.second); ++i) {
                ans.push_back(p.first);
            }
        }
        
        return ans;
    }
};
