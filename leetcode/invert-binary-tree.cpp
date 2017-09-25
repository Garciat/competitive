// https://leetcode.com/problems/invert-binary-tree/

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
    TreeNode* invertTree(TreeNode* root) {
        work(root);
        return root;
    }
    
    void work(TreeNode *node) {
        if (!node) return;
        swap(node->left, node->right);
        invertTree(node->left);
        invertTree(node->right);
    }
};
