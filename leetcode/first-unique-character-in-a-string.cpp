// https://leetcode.com/problems/first-unique-character-in-a-string/

class Solution {
public:
    int firstUniqChar(string s) {
        int positions[26] = {0};
        
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i] - 'a';
            if (positions[c] == -1) {
                continue;
            } else {
                if (positions[c] == 0) {
                    positions[c] = i + 1;
                } else {
                    positions[c] = -1;
                }
            }
        }
        
        int ans = INT_MAX;
        for (int pos : positions) {
            if (pos <= 0) continue;
            ans = min(ans, pos);
        }
        
        return ans == INT_MAX ? -1 : ans - 1;
    }
};
