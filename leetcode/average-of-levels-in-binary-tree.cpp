// https://leetcode.com/problems/average-of-levels-in-binary-tree/

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
    vector<double> averageOfLevels(TreeNode* root) {
        unordered_map<int, pair<long long, int>> m;
        
        work(m, root, 0);
        
        vector<double> ans;
        
        for (int i = 0; ; ++i) {
            auto it = m.find(i);
            if (it == m.end())
                break;
            ans.push_back((double)it->second.first / it->second.second);
        }
        
        return ans;
    }
    
    void work(unordered_map<int, pair<long long, int>>& m, TreeNode* node, int level) {
        if (!node) return;
        m[level].first += node->val;
        m[level].second += 1;
        work(m, node->left, level+1);
        work(m, node->right, level+1);
    }
};
