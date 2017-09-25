// https://leetcode.com/problems/diameter-of-binary-tree/

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
    int diameterOfBinaryTree(TreeNode* root) {
        return work(root).second;
    }
    
    pair<int, int> work(TreeNode* node, int level = 0) {
        if (!node) return { level-1, 0 };
        
        auto p = work(node->left, level+1);
        auto q = work(node->right, level+1);
        
        auto r = (p.first - level) + (q.first - level);
        
        return { max(p.first, q.first), max(max(p.second, q.second), r) };
    }
};
