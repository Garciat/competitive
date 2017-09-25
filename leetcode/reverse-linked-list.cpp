// https://leetcode.com/problems/reverse-linked-list/

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
    ListNode* reverseList(ListNode* head) {
        if (!head) return head;
        return work(head, nullptr);
    }
    
    ListNode* work(ListNode *cur, ListNode *prev) {
        auto next = cur->next;
        cur->next = prev;
        if (!next) return cur;
        return work(next, cur);
    }
};
