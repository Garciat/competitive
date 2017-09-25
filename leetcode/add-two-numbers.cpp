// https://leetcode.com/problems/add-two-numbers/

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return work(l1, l2, 0);
    }
    
    ListNode* work(ListNode *a, ListNode *b, int carry) {
        if (!a && !b && !carry) return nullptr;
        auto x = val(a) + val(b) + carry;
        return node(x % 10, work(next(a), next(b), x / 10));
    }
    
    static ListNode* node(int val, ListNode *next) {
        auto n = new ListNode(val);
        n->next = next;
        return n;
    }
    
    static int val(ListNode *x) {
        return x ? x->val : 0;
    }
    
    static ListNode* next(ListNode *x) {
        return x ? x->next : nullptr;
    }
};
