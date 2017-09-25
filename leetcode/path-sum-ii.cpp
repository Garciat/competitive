// https://leetcode.com/problems/path-sum-ii/

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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> ans;
        work(ans, root, 0, sum, {});
        return ans;
    }
    
    void work(vector<vector<int>>& ans, TreeNode* node, int curr, int target, vector<int> path) {
        if (!node)
            return;
        
        path.push_back(node->val);
        
        curr += node->val;
        
        if (curr == target && !node->left && !node->right)
            ans.push_back(path);
        
        work(ans, node->left, curr, target, path);
        work(ans, node->right, curr, target, path);
    }
};
