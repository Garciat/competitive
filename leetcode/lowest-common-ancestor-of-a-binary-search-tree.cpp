// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        auto p_path = findPath(root, p);
        auto q_path = findPath(root, q);
        
        assert(p_path.size() > 0);
        assert(q_path.size() > 0);
        assert(p_path[0] == root);
        assert(q_path[0] == root);
        assert(p_path.back() == p);
        assert(q_path.back() == q);
        
        int i = 1;
        for (; i < min(p_path.size(), q_path.size()); ++i) {
            if (p_path[i] != q_path[i]) {
                break;
            }
        }
        
        assert(p_path[i - 1] == q_path[i - 1]);
        
        return p_path[i - 1];
    }
    
    vector<TreeNode*> findPath(TreeNode* haystack, TreeNode* needle, vector<TreeNode*> path = {}) {
        path.push_back(haystack);
        if (needle->val < haystack->val)
            return findPath(haystack->left, needle, path);
        if (needle->val > haystack->val)
            return findPath(haystack->right, needle, path);
        // so, values are equal. we must explore all equal-value nodes
        path.pop_back(); // so we don't get dupes
        return findEq(haystack, needle, path);
    }
    
    vector<TreeNode*> findEq(TreeNode* haystack, TreeNode* needle, vector<TreeNode*> path = {}) {
        path.push_back(haystack);
        if (haystack == needle) {
            return path;
        }
        if (haystack->left && haystack->left->val == needle->val) {
            auto maybe = findEq(haystack->left, needle, path);
            if (!maybe.empty())
                return maybe;
        }
        if (haystack->right && haystack->right->val == needle->val) {
            auto maybe = findEq(haystack->right, needle, path);
            if (!maybe.empty())
                return maybe;
        }
        return {};
    }
};
