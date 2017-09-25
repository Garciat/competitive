// https://leetcode.com/problems/binary-tree-preorder-traversal/

struct Action {
    enum Tag { TRAVERSE, SHOW };
    
    Tag tag;
    union {
        TreeNode *node;
        int value;
    };
    
    Action(TreeNode *node)
        : tag{TRAVERSE}, node{node}
    {}
    
    Action(int value)
        : tag{SHOW}, value{value}
    {}
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        
        stack<Action> actions;
        actions.push(Action{root});
        
        while (!actions.empty()) {
            auto action = actions.top();
            actions.pop();

            stack<Action> tmp;

            switch (action.tag) {
            case Action::SHOW:
                ans.push_back(action.value);
                break;
            case Action::TRAVERSE:
                auto node = action.node;
                if (!node) continue;           // *
                tmp.push(Action{node->val});   // **
                tmp.push(Action{node->left});  // *
                tmp.push(Action{node->right}); // *
                break;
            }
            
            while (!tmp.empty())
                actions.push(tmp.top()), tmp.pop();
        }
        
        return ans;
    }
};
