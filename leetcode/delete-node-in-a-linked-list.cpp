// https://leetcode.com/problems/delete-node-in-a-linked-list/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        if (!node) return;
        if (!node->next) return;
        node->val = node->next->val;
        if (!node->next->next) {
            node->next = nullptr;
        } else {
            deleteNode(node->next);
        }
    }
};
