// https://leetcode.com/problems/intersection-of-two-linked-lists/

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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        
        auto p = headA;
        auto q = headB;
        
        while (p != q) {
            p = !p ? headB : p->next;
            q = !q ? headA : q->next;
        }
        
        return p;
    }
};
