// https://leetcode.com/problems/merge-k-sorted-lists/

// reverse order
struct Comparer {
    bool operator()(ListNode* a, ListNode *b) {
        return b->val < a->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Comparer> pq;
        
        for (auto head : lists)
            if (head)
                pq.push(head);
        
        ListNode root{INT_MIN};
        ListNode *head = &root;
        
        while (!pq.empty()) {
            auto next = pq.top();
            pq.pop();
            
            if (next->next)
                pq.push(next->next);
            
            head->next = next;
            
            head = next;
        }
        
        head->next = nullptr;
        
        return root.next;
    }
};
