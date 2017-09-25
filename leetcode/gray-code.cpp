// https://leetcode.com/problems/gray-code/

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> ans;
        ans.push_back(0);
        int k = 1;
        for (int i = 0; i < n; ++i) {
            auto m = ans.size();
            ans.reserve(ans.size() * 2);
            copy(ans.rbegin(), ans.rend(), back_inserter(ans));
            for (int j = m; j < ans.size(); ++j) {
                ans[j] |= k;
            }
            k <<= 1;
        }
        return ans;
    }
};
