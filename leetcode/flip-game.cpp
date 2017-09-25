// https://leetcode.com/problems/flip-game/

class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        vector<string> ans;
        for (int i = 1; i < s.size(); ++i) {
            if (s[i-1] == s[i] && s[i] == '+') {
                ans.push_back(s);
                ans.back()[i-1] = '-';
                ans.back()[i-0] = '-';
            }
        }
        return ans;
    }
};
