// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return work(nums, 0, nums.size());
    }
    
    TreeNode* work(const vector<int>& ns, int i, int j) {
        if (i >= j) return nullptr;
        int m = (i + j) / 2;
        auto node = new TreeNode{ns[m]};
        node->left = work(ns, i, m);
        node->right = work(ns, m+1, j);
        return node;
    }
};
