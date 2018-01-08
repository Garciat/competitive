// https://leetcode.com/problems/count-binary-substrings/

class Solution {
public:
    int countBinarySubstrings(string s) {
        int ans = 0;
        int i = 0;
        int n = 0;
        int k = s.size();
        while (i < k) {
            int m = 0;
            while (s[i] == s[i + m]) m += 1;
            ans += min(n, m);
            n = m;
            i += m;
        }
        return ans;
    }
};
