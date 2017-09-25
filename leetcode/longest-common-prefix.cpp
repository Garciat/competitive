// https://leetcode.com/problems/longest-common-prefix/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        
        int i = 0;
        for (;;) {
            bool ok = true;
            char c = 0;
            
            for (auto& s : strs) {
                if (i == s.size()) {
                    ok = false;
                    break;
                }
                if (!c) c = s[i];
                ok &= c == s[i];
            }
            
            if (!ok) break;
            
            i += 1;
        }
        
        return strs[0].substr(0, i);
    }
};
