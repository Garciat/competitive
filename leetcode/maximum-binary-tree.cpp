// https://leetcode.com/problems/maximum-binary-tree/

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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return work(nums, 0, nums.size());
    }
    
    TreeNode* work(vector<int>& ns, int i, int j) {
        if (i >= j) return nullptr;
        auto it = max_element(ns.begin() + i, ns.begin() + j);
        int k = it - ns.begin();
        auto node = new TreeNode(*it);
        node->left = work(ns, i, k);
        node->right = work(ns, k + 1, j);
        return node;
    }
};
