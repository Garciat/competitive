// https://leetcode.com/problems/first-unique-character-in-a-string/

class Solution {
public:
    int firstUniqChar(string s) {
        int counts[27] {};
        
        for (char c : s) {
            counts[c - 'a'] += 1;
        }
        
        for (int i = 0; i < s.size(); ++i) {
            if (counts[s[i] - 'a'] == 1) {
                return i;
            }
        }
        
        return -1;
    }
};
