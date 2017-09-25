// https://leetcode.com/problems/length-of-last-word/

class Solution {
public:
    int lengthOfLastWord(string s) {
        auto q = s.find_last_not_of(' ');
        if (q == string::npos) {
            return 0;
        }
        auto p = s.rfind(' ', q);
        return p == string::npos ? q + 1 : q - p;
    }
};
