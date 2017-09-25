// https://leetcode.com/problems/reverse-string/

class Solution {
public:
    string reverseString(string s) {
        int i = 0;
        int j = s.size() - 1;
        while (i < j) {
            swap(s[i], s[j]);
            i += 1;
            j -= 1;
        }
        return s;
    }
};
