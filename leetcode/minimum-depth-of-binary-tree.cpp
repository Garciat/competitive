// https://leetcode.com/problems/minimum-depth-of-binary-tree/

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
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        return work(root, 1);
    }
    int work(TreeNode *node, int d) {
        if (!node->left && !node->right) {
            return d;
        }
        int a = INT_MAX;
        if (node->left)
            a = min(a, work(node->left, d+1));
        if (node->right)
            a = min(a, work(node->right, d+1));
        return a;
    }
};
