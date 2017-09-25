// https://leetcode.com/problems/implement-strstr/

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        for (int i = 0; i < (int)haystack.size() - (int)needle.size() + 1; ++i) {
            if (equal(needle.begin(), needle.end(), haystack.begin()+i)) {
                return i;
            }
        }
        return -1;
    }
};
