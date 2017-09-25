// https://leetcode.com/problems/path-sum/

/*

fails:

    didn't pay attention to LEAF detail
    
    didn't consider negatives

*/

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
    bool hasPathSum(TreeNode* root, int sum) {
        return work(root, 0, sum);
    }
    
    bool work(TreeNode *node, int s, int target) {
        if (node == nullptr) {
            return false;
        }
        int ns = s + node->val;
        if (ns == target && !node->left && !node->right) {
            return true;
        }
        return work(node->left, ns, target) || work(node->right, ns, target);
    }
};
