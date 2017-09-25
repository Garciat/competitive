// https://leetcode.com/problems/reverse-string-ii/

class Solution {
public:
    string reverseStr(string s, int k) {
        int i = 0;
        
        for (;;) {
            if (i + 2 * k < s.size()) {
                reverse(s.begin() + i, s.begin() + i + k);
                i += 2 * k;
            } else if (i + k < s.size()) {
                reverse(s.begin() + i, s.begin() + i + k);
                break;
            } else {
                reverse(s.begin() + i, s.end());
                break;
            }
        }
        
        return s;
    }
};
