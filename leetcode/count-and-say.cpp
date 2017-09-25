// https://leetcode.com/problems/count-and-say/


class Solution {
public:
    string countAndSay(int n) {
        string s = "1";
        
        for (int i = 1; i < n; ++i) {
            s = countAndSay(s);
        }
        
        return s;
    }
    
    string countAndSay(const string &s) {
        string t = "0";
        char c = s.front();
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == c) {
                t.back() += 1;
            } else {
                t += c;
                t += '1';
                c = s[i];
            }
        }
        t += s.back();
        return t;
    }
};
