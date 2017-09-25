// https://leetcode.com/problems/pascals-triangle-ii/

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> r = {1};
        
        for (int i = 0; i < rowIndex; ++i) {
            vector<int> n;
            n.push_back(1);
            for (int j = 1; j < r.size(); ++j) {
                n.push_back(r[j-1] + r[j]);
            }
            n.push_back(1);
            r = n;
        }
        
        return r;
    }
};
