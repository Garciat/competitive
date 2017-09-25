// https://leetcode.com/problems/binary-tree-tilt/

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
    int findTilt(TreeNode* root) {
        return work(root);
    }
    
    int work(TreeNode *node) {
        if (!node) return 0;
        int tilt = abs(sum(node->left) - sum(node->right));
        return tilt + work(node->left) + work(node->right);
    }
    
    int sum(TreeNode *node) {
        if (!node) return 0;
        return node->val + sum(node->left) + sum(node->right);
    }
};
