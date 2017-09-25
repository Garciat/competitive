// https://leetcode.com/problems/symmetric-tree/

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
    bool isSymmetric(TreeNode* root) {
        return !root || work(root->left, root->right);
    }
    
    bool work(TreeNode* left, TreeNode* right) {
        if (!left || !right)
            return left == right;
        if (left->val != right->val)
            return false;
        return work(left->left, right->right) && work(left->right, right->left);
    }
};
