// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "()";
        return "(" + to_string(root->val)
             + " " + serialize(root->left)
             + " " + serialize(root->right)
             + ")";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int i = 0;
        return work(data, i);
    }
    
    TreeNode* work(const string &data, int &i) {
        if (data[i] == '(' && data[i+1] == ')') {
            i += 2;
            return nullptr;
        }
        i += 1; // '('
        int64_t val = 0;
        bool neg = false;
        if (data[i] == '-') {
            neg = true;
            i += 1;
        }
        while (data[i] != ' ') {
            val *= 10;
            val += data[i] - '0';
            i += 1;
        }
        val *= neg ? -1 : 1;
        i += 1; // ' '
        auto t = new TreeNode{(int)val};
        t->left = work(data, i);
        i += 1; // ' '
        t->right = work(data, i);
        i += 1; // ')'
        return t;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
