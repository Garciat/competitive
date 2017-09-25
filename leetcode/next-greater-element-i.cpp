// https://leetcode.com/problems/next-greater-element-i/

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        vector<int> ans;
        for (int x : findNums) {
            auto it = find(begin(nums), end(nums), x);
            if (it == end(nums)) {
                ans.push_back(-1);
                continue;
            }
            auto ot = find_if(it, end(nums), [it](int y) { return y > *it; });
            if (ot == end(nums)) {
                ans.push_back(-1);
                continue;
            }
            ans.push_back(*ot);
        }
        return ans;
    }
};
