// https://leetcode.com/problems/add-two-numbers-ii/

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
    ListNode* addTwoNumbers(ListNode* xs, ListNode* ys) {
        auto ans = prep(nullptr, nullptr, hello(xs, ys));
        return ans->val == 0 ? ans->next : ans;
    }
    
    ListNode* hello(ListNode *xs, ListNode *ys) {
        int n = length(xs);
        int m = length(ys);
        
        if (m > n)
            return work(ys, m, xs, n);
        else
            return work(xs, n, ys, m);
    }
    
    ListNode* work(ListNode *xs, int n, ListNode *ys, int m) {
        if (n == m) {
            if (n == 1) {
                return new ListNode(xs->val + ys->val);
            } else {
                return prep(xs, ys, work(xs->next, n-1, ys->next, n-1));
            }
        } else {
            return prep(xs, nullptr, work(xs->next, n-1, ys, m));
        }
    }
    
    ListNode* prep(ListNode *a, ListNode *b, ListNode *sub) {
        int x = sub->val / 10;
        if (a) x += a->val;
        if (b) x += b->val;
        auto cur = new ListNode(x);
        cur->next = sub;
        sub->val %= 10;
        return cur;
    }
    
    int length(ListNode *node) {
        int len = 0;
        while (node) {
            len += 1;
            node = node->next;
        }
        return len;
    }
};
