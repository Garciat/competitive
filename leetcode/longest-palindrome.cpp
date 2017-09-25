// https://leetcode.com/problems/longest-palindrome/

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> z;
        
        for (char c : s) {
            z[c] += 1;
        }
        
        bool has_odd = false;
        int pairs = 0;
        
        for (auto& p : z) {
            if (p.second % 2 == 1) {
                has_odd = true;
            }
            pairs += p.second / 2;
        }
        
        return 2 * pairs + (has_odd ? 1 : 0);
    }
};
