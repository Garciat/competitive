// https://leetcode.com/problems/find-largest-value-in-each-tree-row/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        unordered_map<int, int> m;
        
        work(m, root, 0);
        
        vector<int> ans(m.size());
        
        for (int i = 0; ; ++i) {
            auto it = m.find(i);
            if (it == m.end()) break;
            ans[it->first] = it->second;
        }
        
        return ans;
    }
    
    void work(unordered_map<int, int>& m, TreeNode* node, int level) {
        if (!node) return;
        auto it = m.find(level);
        if (it == m.end())
            m[level] = node->val;
        else
            it->second = max(it->second, node->val);
        work(m, node->left, level + 1);
        work(m, node->right, level + 1);
    }
};
