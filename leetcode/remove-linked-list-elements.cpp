// https://leetcode.com/problems/remove-linked-list-elements/

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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode root{0};
        root.next = head;
        
        ListNode *prev = &root;
        ListNode *curr = prev->next;
        
        while (curr) {
            if (curr->val == val) {
                curr = prev->next = curr->next;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        
        return root.next;
    }
};
