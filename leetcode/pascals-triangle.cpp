// https://leetcode.com/problems/pascals-triangle/

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        
        if (numRows) {
            ans.emplace_back(vector<int>{1});
        }
        
        for (int i = 1; i < numRows; ++i) {
            auto& r = ans.back();
            vector<int> n;
            n.push_back(1);
            for (int j = 1; j < r.size(); ++j) {
                n.push_back(r[j-1] + r[j]);
            }
            n.push_back(1);
            ans.push_back(n);
        }
        
        return ans;
    }
};
