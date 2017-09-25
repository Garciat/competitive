// https://leetcode.com/problems/sum-of-left-leaves/

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
    int sumOfLeftLeaves(TreeNode* root) {
        return work(root);
    }
    
    int work(TreeNode *node) {
        if (!node) return 0;
        if (isLeaf(node->left)) {
            return node->left->val + work(node->right);
        } else {
            return work(node->left) + work(node->right);
        }
    }
    
    static bool isLeaf(TreeNode *node) {
        if (!node) return false;
        return !node->left && !node->right;
    }
};
