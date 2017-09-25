// https://leetcode.com/problems/number-of-segments-in-a-string/

class Solution {
public:
    int countSegments(string s) {
        int ans = 0;
        int i = 0;
        for (;;) {
            while (i < s.size() && s[i] == ' ')
                ++i;
            
            if (i == s.size())
                break;
            
            while (i < s.size() && s[i] != ' ')
                ++i;
            
            ans += 1;
        }
        return ans;
    }
};
