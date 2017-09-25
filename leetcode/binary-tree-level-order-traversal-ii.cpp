// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root) return {};
        
        unordered_map<int, vector<int>> levels;
        
        work(levels, root, 0);
        
        vector<vector<int>> ans(levels.size());
        
        for (auto p : levels) {
            ans[levels.size() - p.first - 1] = p.second;
        }
        
        return ans;
    }
    
    void work(unordered_map<int, vector<int>>& levels, TreeNode* node, int level) {
        if (!node) return;
        levels[level].push_back(node->val);
        work(levels, node->left, level+1);
        work(levels, node->right, level+1);
    }
};
