// https://leetcode.com/problems/merge-two-sorted-lists/

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

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode ans {INT_MIN};
        
        ListNode* out = &ans;
        
        for (;;) {
            if (!l1) {
                out->next = l2;
                break;
            }
            if (!l2) {
                out->next = l1;
                break;
            }
            
            if (l2->val < l1->val) {
                out->next = l2;
                l2 = l2->next;
            } else {
                out->next = l1;
                l1 = l1->next;
            }
            
            out = out->next;
        }
        
        return ans.next;
    }
};
