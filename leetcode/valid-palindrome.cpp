// https://leetcode.com/problems/valid-palindrome/

class Solution {
public:
    bool isPalindrome(string s) {
        if (s.empty()) return true;
        
        string t;
        for (char c : s) {
            if (isdigit(c)) {
                t += c;
            } else if (isalpha(c)) {
                t += tolower(c);
            }
        }
        
        for (int i = 0; i < t.size() / 2; ++i) {
            if (t[i] != t[t.size() - i - 1]) {
                return false;
            }
        }
        
        return true;
    }
};
