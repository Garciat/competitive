// https://leetcode.com/problems/add-one-row-to-tree/

class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (!root) return root;
        auto tmp = node(0, root, nullptr);
        work(tmp, v, d, 0);
        return tmp->left;
    }
    
    void work(TreeNode *n, int v, int d, int i) {
        if (!n) return;
        if (i + 1 == d) {
            n->left = node(v, n->left, nullptr);
            n->right = node(v, nullptr, n->right);
        } else {
            work(n->left, v, d, i+1);
            work(n->right, v, d, i+1);
        }
    }
    
    static TreeNode* node(int v, TreeNode *x, TreeNode *y) {
        auto t = new TreeNode{v};
        t->left = x;
        t->right = y;
        return t;
    }
};
