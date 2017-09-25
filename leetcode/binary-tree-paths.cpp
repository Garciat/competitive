// https://leetcode.com/problems/binary-tree-paths/

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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        work(ans, root, "");
        return ans;
    }
    
    void work(vector<string>& ans, TreeNode *node, string pre) {
        if (!node) return;
        
        pre += to_string(node->val);

        if (!node->left && !node->right) {
            ans.push_back(pre);
        } else {
            pre += "->";
            work(ans, node->left, pre);
            work(ans, node->right, pre);
        }
    }
};
