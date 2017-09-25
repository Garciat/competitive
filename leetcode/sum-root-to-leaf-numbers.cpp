// https://leetcode.com/problems/sum-root-to-leaf-numbers/

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
    int sumNumbers(TreeNode* root) {
        return work(root, 0);
    }
    
    int work(TreeNode *node, int val) {
        if (!node)
            return 0;
        int next = 10 * val + node->val;
        if (!node->left && !node->right)
            return next;
        return work(node->left, next)
             + work(node->right, next);
    }
};
