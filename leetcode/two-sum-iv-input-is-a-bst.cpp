// https://leetcode.com/problems/two-sum-iv-input-is-a-bst/

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        return work(root, root, k);
    }
    
    bool work(TreeNode* root, TreeNode* node, int k) {
        if (!node) return false;
        
        if (find(root, node, k - node->val, false)) {
            return true;
        }
        
        return work(root, node->left, k) || work(root, node->right, k);
    }
    
    bool find(TreeNode* node, TreeNode* self, int x, bool match) {
        if (!node) return false;
        
        if (match && node->val == x && node != self) {
            return true;
        }
        
        if (x < node->val)
            return find(node->left, self, x, true);
        else if (x > node->val)
            return find(node->right, self, x, true);
        else
            return false;
    }
};
