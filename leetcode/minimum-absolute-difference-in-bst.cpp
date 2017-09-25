// https://leetcode.com/problems/minimum-absolute-difference-in-bst/

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
    int getMinimumDifference(TreeNode* root) {
        return walk(root);
    }
    
    int walk(TreeNode *node) {
        int best = work(node);
        if (node->left)
            best = min(best, walk(node->left));
        if (node->right)
            best = min(best, walk(node->right));
        return best;
    }
    
    int work(TreeNode *node) {
        int best = INT_MAX;
        if (node->left)
            best = min(best, abs(node->val - find_max(node->left)));
        if (node->right)
            best = min(best, abs(node->val - find_min(node->right)));
        return best;
    }
    
    int find_max(TreeNode *node) {
        if (!node->right) return node->val;
        return find_max(node->right);
    }
    
    int find_min(TreeNode *node) {
        if (!node->left) return node->val;
        return find_min(node->left);
    }
};
