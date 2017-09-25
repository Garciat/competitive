// https://leetcode.com/problems/valid-palindrome-ii/


class Solution {
public:
    bool validPalindrome(string s) {
        return work(s, 0, s.size() - 1, true);
    }
    
    bool work(const string& s, int i, int j, bool r) {
        if (i >= j) return true;
        if (s[i] == s[j]) {
            return work(s, i+1, j-1, r);
        } else if (r) {
            return work(s, i+1, j, false) || work(s, i, j-1, false);
        } else {
            return false;
        }
    }
};
