// https://leetcode.com/problems/find-bottom-left-tree-value/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct Answer {
    int depth, value;
};

bool operator<(Answer a, Answer b) {
    return a.depth < b.depth;
}

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        return work(root, 0).value;
    }
    
    Answer work(TreeNode *node, int depth) {
        Answer a { depth, node->val };
        // because std::max(x, y) will return x if x==y (max is stable),
        //   we must try the left branch first,
        //   which creates a "preference" for
        //   left-most same-depth answers
        if (node->left)
            a = max(a, work(node->left, depth+1));
        if (node->right)
            a = max(a, work(node->right, depth+1));
        return a;
    }
};
