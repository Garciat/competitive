// https://leetcode.com/problems/valid-parenthesis-string/

class Solution {
public:
    bool checkValidString(string s) {
        return work(s, 0);
    }
    
    bool work(const string& s, int i, int p = 0) {
        if (p < 0) return false;
        if (i >= s.size()) return p == 0;
        switch (s[i]) {
            case '(':
                return work(s, i+1, p+1);
            case ')':
                return work(s, i+1, p-1);
            case '*':
                return work(s, i+1, p) || work(s, i+1, p+1) || work(s, i+1, p-1);
        }
    }
};
