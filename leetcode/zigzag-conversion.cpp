// https://leetcode.com/problems/zigzag-conversion/

class Solution {
public:
    string convert(string s, int n) {
        if (n <= 1) return s;
        
        vector<string> rows(n, "");
        
        int k = 0;
        int w = 1;
        for (char c : s) {
            rows[k] += c;
            
            k += w;
            if (k ==   0) w = +1;
            if (k == n-1) w = -1;
        }
        
        string ans;
        for (string& r : rows) {
            ans += r;
        }
        return ans;
    }
};
