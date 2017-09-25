// https://leetcode.com/problems/subtree-of-another-tree/

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
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (s == t) return true;
        if (!s || !t) return false;
        return equal(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
    }
    
    bool equal(TreeNode* s, TreeNode *t) {
        if (s == t) return true;
        if (!s || !t) return false;
        return s->val == t->val && equal(s->left, t->left) && equal(s->right, t->right);
    }
};
