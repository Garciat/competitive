// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        
        deque<TreeNode*> curr_level, next_level;
        next_level.push_back(root);
        
        int depth = 0;
        
        while (!next_level.empty()) {
            
            swap(curr_level, next_level);
            next_level.clear();
            
            ans.emplace_back();
            
            while (!curr_level.empty()) {
                TreeNode* node;
                
                if (depth % 2 == 0) {
                    node = curr_level.front();
                    curr_level.pop_front();
                } else {
                    node = curr_level.back();
                    curr_level.pop_back();
                }
                
                if (!node) continue;
                
                ans.back().push_back(node->val);

                if (depth % 2 == 0) {
                    next_level.push_back(node->left);
                    next_level.push_back(node->right);
                } else {
                    next_level.push_front(node->right);
                    next_level.push_front(node->left);
                }
            }
            
            if (ans.back().size() == 0)
                ans.pop_back();
            
            depth += 1;
        }
        
        return ans;
    }
};
