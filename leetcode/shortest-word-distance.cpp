// https://leetcode.com/problems/shortest-word-distance/

class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int pa = -1;
        int pb = -1;
        int ans = INT_MAX;
        
        for (int i = 0; i < words.size(); ++i) {
            if (words[i] == word1) {
                pa = i;
            } else if (words[i] == word2) {
                pb = i;
            }
            if (pa != -1 && pb != -1) {
                ans = min(ans, abs(pa - pb));
            }
        }
        
        return ans;
    }
};
