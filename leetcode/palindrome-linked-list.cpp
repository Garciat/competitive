// https://leetcode.com/problems/palindrome-linked-list/

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

    ListNode* reverse(ListNode *node) {
        ListNode *prev = nullptr;
        
        while (node) {
            ListNode *tmp = node->next;
            node->next = prev;
            prev = node;
            node = tmp;
        }
        
        return prev;
    }

    bool isPalindrome(ListNode* head) {
        if (head == nullptr) {
            return true;
        }
        if (head->next == nullptr) {
            return true;
        }
        
        // fast/slow pointer algo
        ListNode *p1 = head;
        ListNode *p2 = head;
        
        // move fwd until fast ptr's distance to the end is 0 or 1
        // if 0: this is an odd-length list
        //    -> and p1 will point to (1 + n / 2)'th node
        //
        // if 1: this is an even-length list
        //    -> and p1 will point to (n / 2)'th node
        while (p2->next && p2->next->next) {
            p1 = p1->next;
            p2 = p2->next->next;
        }
        
        // neither will be null
        assert(p1);
        assert(p2);
        
        // make it point to the 2nd half of the list
        p1 = p1->next;
        
        ListNode *pL = head;
        ListNode *pR = reverse(p1);
        
        while (pR) {
            assert(pL);
            if (pL->val != pR->val) {
                return false;
            }
            pL = pL->next;
            pR = pR->next;
        }
        
        return true;
    }
};
