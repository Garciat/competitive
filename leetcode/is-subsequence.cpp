// https://leetcode.com/problems/is-subsequence/

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0;
        for (char c : s) {
            auto pos = t.find_first_of(c, i);
            if (pos == string::npos)
                return false;
            i = pos + 1;
        }
        return true;
    }
};
