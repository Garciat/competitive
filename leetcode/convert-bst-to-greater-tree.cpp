// https://leetcode.com/problems/convert-bst-to-greater-tree/

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
    TreeNode* convertBST(TreeNode* root) {
        work(root);
        return root;
    }
    
    int work(TreeNode* node, int sum = 0, int app = 0) {
        if (!node) return 0;
        
        auto r = work(node->right, sum, app);
        auto c = node->val;
        auto l = work(node->left, sum, c + r + app);
        
        node->val += r + app;
        
        return c + r + l + sum;
    }
};
