// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    TreeNode* sortedListToBST(ListNode* head) {
        return work(head, nullptr);
    }
    
    TreeNode* work(ListNode* first, ListNode *last) {
        if (first == last) return nullptr;
        
        auto slow = first;
        auto fast = first;
        
        while (fast != last && fast->next != last) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        auto node = new TreeNode{slow->val};
        node->left = work(first, slow);
        node->right = work(slow->next, last);
        
        return node;
    }
};
