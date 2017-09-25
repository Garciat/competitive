// https://leetcode.com/problems/print-binary-tree/

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
    vector<vector<string>> printTree(TreeNode* root) {
        if (!root) return {};
        
        int m = height(root);
        int n = (1 << m) - 1;
        
        vector<vector<string>> ans(m, vector<string>(n, ""));
        
        work(ans, root, 0, 0, n);
        
        return ans;
    }
    
    void work(vector<vector<string>>& ans, TreeNode* node, int h, int i, int j) {
        if (!node) return;
        int k = (i + j) / 2;
        ans[h][k] = to_string(node->val);
        work(ans, node->left, h+1, i, k);
        work(ans, node->right, h+1, k+1, j);
    }
    
    int height(TreeNode* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }
};
