// https://leetcode.com/problems/intersection-of-two-arrays/

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> ans;
        set<int> known(begin(nums1), end(nums1));
        for (int x : nums2) {
            if (known.find(x) != known.end())
                ans.insert(x);
        }
        return vector<int>(begin(ans), end(ans));
    }
};
