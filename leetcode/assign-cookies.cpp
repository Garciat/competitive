// https://leetcode.com/problems/assign-cookies/

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(begin(g), end(g));
        sort(begin(s), end(s));
        
        int ig = 0;
        int is = 0;
        
        int ans = 0;
        
        while (ig < g.size() && is < s.size()) {
            if (g[ig] <= s[is]) {
                ans += 1;
                ig += 1;
                is += 1;
            } else {
                is += 1;
            }
        }
        
        return ans;
    }
};
