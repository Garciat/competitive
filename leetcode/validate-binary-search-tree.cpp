// https://leetcode.com/problems/validate-binary-search-tree/

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
    bool isValidBST(TreeNode* root) {
        return work(root, LLONG_MIN, LLONG_MAX);
    }
    
    bool work(TreeNode* node, int64_t lo, int64_t hi) {
        if (!node) return true;
        return node->val > lo
            && node->val < hi
            && work(node->left, lo, node->val)
            && work(node->right, node->val, hi);
    }
};
