// https://leetcode.com/problems/isomorphic-strings/

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int counts[256] {};
        int countt[256] {};
        fill(begin(counts), end(counts), 1000);
        fill(begin(countt), end(countt), 1000);
        
        for (int i = 0; i < s.size(); ++i) {
            int d = s[i] - t[i];
            int &cs = counts[s[i]];
            int &ct = countt[t[i]];
            
            if (cs == 1000) {
                cs = d;
            }
            if (ct == 1000) {
                ct = d;
            }
            
            if (cs != d) {
                return false;
            }
            if (ct != d) {
                return false;
            }
        }
        
        return true;
    }
};
