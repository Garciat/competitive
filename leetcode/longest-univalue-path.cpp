// https://leetcode.com/problems/longest-univalue-path/

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
    int longestUnivaluePath(TreeNode* root) {
        return joint(root);
    }
    
    int joint(TreeNode* n) {
        if (!n) return 0;
        return max(
            max(joint(n->left), joint(n->right)),
            path(n->left, n->val) + path(n->right, n->val)
        );
    }
    
    int path(TreeNode* n, int k) {
        if (!n) return 0;
        if (n->val == k) {
            return 1 + max(path(n->left, k), path(n->right, k));
        } else {
            return 0;
        }
    }
};
