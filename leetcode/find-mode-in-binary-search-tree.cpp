// https://leetcode.com/problems/find-mode-in-binary-search-tree/


class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        if (!root) return {};
        
        vector<int> ans;
        int n = 0;
        int m = 0;
        int k = 0;
        
        auto flush = [&] () {
            if (m > n) {
                ans.clear();
                ans.push_back(k);
                n = m;
            } else if (m == n) {
                ans.push_back(k);
            }
            m = 1;
        };
        
        in_order(root, [&] (int x) {
            if (x == k) {
                m += 1;
            } else {
                flush();
            }
            k = x;
        });
        
        flush();
        
        return ans;
    }
    
    template <typename F>
    void in_order(TreeNode* node, F &&f) {
        if (!node) return;
        in_order(node->left, f);
        f(node->val);
        in_order(node->right, f);
    }
};
