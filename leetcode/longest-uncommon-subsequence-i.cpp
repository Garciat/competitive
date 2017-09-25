// https://leetcode.com/problems/longest-uncommon-subsequence-i/

class Solution {
public:
    int findLUSlength(string a, string b) {
        if (a.size() != b.size()) {
            return max(a.size(), b.size());
        }
        for (int i = 0; i < a.size(); ++i) {
            if (b.find(a.c_str() + i, 0, a.size() - i) == string::npos) {
                return a.size() - i;
            }
        }
        return -1;
    }
};
