// https://leetcode.com/problems/generate-parentheses/

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        work(ans, 0, n, "");
        return ans;
    }
    
    void work(vector<string>& ans, int open, int left, string pre) {
        if (!open) {
            if (left) {
                work(ans, open+1, left-1, pre + "(");
            } else {
                ans.push_back(pre);
            }
        } else {
            if (left) {
                work(ans, open+1, left-1, pre + "(");
            }
            work(ans, open-1, left, pre + ")");
        }
    }
    
};
