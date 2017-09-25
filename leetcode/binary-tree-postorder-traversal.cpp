// https://leetcode.com/problems/binary-tree-postorder-traversal/

struct Item {
    enum Tag { NODE, VALUE };
    
    Tag tag;
    union {
        TreeNode *node;
        int value;
    };
    
    Item(TreeNode *node)
        : tag{NODE}, node{node}
    {}
    
    Item(int value)
        : tag{VALUE}, value{value}
    {}
};

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        
        stack<Item> items;
        items.push(Item{root});
        
        while (!items.empty()) {
            auto item = items.top();
            items.pop();
            
            if (item.tag == Item::VALUE) {
                ans.push_back(item.value);
            } else if (item.node) {
                items.push(Item{item.node->left});
                items.push(Item{item.node->right});
                items.push(Item{item.node->val});
            }
        }
        
        reverse(ans.begin(), ans.end());
        
        return ans;
    }
};
