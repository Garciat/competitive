// https://leetcode.com/problems/balanced-binary-tree/

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
    bool isBalanced(TreeNode* root) {
        return work(root, 0) != -1;
    }
    
    int work(TreeNode* node, int d) {
        if (!node) return d;
        
        int a = work(node->left, d+1);
        int b = work(node->right, d+1);
        
        return abs(a - b) <= 1 ? max(a, b) : -1;
    }
};
