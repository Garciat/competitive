// https://leetcode.com/problems/range-addition-ii/

class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        int r = m;
        int s = n;
        
        for (vector<int> &op : ops) {
            int i = op[0];
            int j = op[1];
            
            r = min(r, i);
            s = min(s, j);
        }
        
        return r * s;
    }
};
