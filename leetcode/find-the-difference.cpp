// https://leetcode.com/problems/find-the-difference/

class Solution {
public:
    char findTheDifference(string s, string t) {
        int count[27]{};
        
        for (char c : s) {
            count[c - 'a'] += 1;
        }
        
        for (char c : t) {
            if (--count[c-'a'] < 0) {
                return c;
            }
        }
    }
};
