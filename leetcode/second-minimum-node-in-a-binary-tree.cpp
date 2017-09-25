// https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/

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
    int findSecondMinimumValue(TreeNode* root) {
        if (!root) return -1;
        return work(root, root->val);
    }
    
    int work(TreeNode *node, int r) {
        if (!node) return -1;
        if (node->val != r) return node->val;
        int a = work(node->left, r);
        int b = work(node->right, r);
        if (a == -1) return b;
        if (b == -1) return a;
        return min(a, b);
    }
};
