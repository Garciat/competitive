// https://leetcode.com/problems/path-sum-iii/

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
    int pathSum(TreeNode* root, int sum) {
        unordered_map<int, int> mem;
        mem[0] += 1;
        return work(mem, root, 0, sum);
    }
    
    int work(unordered_map<int, int>& mem, TreeNode* node, int curr, int target) {
        if (!node)
            return 0;
        
        curr += node->val;
        
        int res = mem[curr - target];
        
        mem[curr] += 1;
        res += work(mem, node->left, curr, target) + work(mem, node->right, curr, target);
        mem[curr] -= 1;
        
        return res;
    }
};
