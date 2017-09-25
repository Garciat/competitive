// https://leetcode.com/problems/reverse-words-in-a-string-iii/

class Solution {
public:
    string reverseWords(string s) {
        istringstream iss{s};
        ostringstream oss;
        work(iss, oss, false);
        return oss.str();
    }
    
    void work(istream &is, ostream &os, bool space) {
        static string s;
        is >> s;
        if (!is) return;
        reverse(s.begin(), s.end());
        if (space) os << ' ';
        os << s;
        work(is, os, true);
    }
};
