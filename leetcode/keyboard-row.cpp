// https://leetcode.com/problems/keyboard-row/

class Solution {
public:
    int letter_row[27];
    
    vector<string> findWords(vector<string>& words) {
        what("qwertyuiop", 0);
        what("asdfghjkl", 1);
        what("zxcvbnm", 2);
        
        vector<string> ans;
        
        for (string &word : words) {
            int r = -1;
            for (char c : word) {
                int s = letter_row[tolower(c) - 'a'];
                if (r != -1 && r != s) {
                    goto nope;
                }
                r = s;
            }
            ans.emplace_back(std::move(word));
        nope:
            ;
        }
        
        return ans;
    }
    
    void what(const char *s, int n) {
        while (*s) {
            letter_row[*s++ - 'a'] = n;
        }
    }
};
