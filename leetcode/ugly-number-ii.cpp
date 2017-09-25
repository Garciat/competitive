// https://leetcode.com/problems/ugly-number-ii/

class Solution {
    using PQType = priority_queue<int64_t, vector<int64_t>, greater<int64_t>>;
    
public:
    int nthUglyNumber(int n) {
        PQType pq;
        unordered_set<int64_t> seen;
        pq.push(1);
        
        while (n > 1) {
            int x = pq.top();
            pq.pop();
            
            work(pq, seen, x, 2);
            work(pq, seen, x, 3);
            work(pq, seen, x, 5);
            
            n -= 1;
        }
        
        return pq.top();
    }
    
    void work(PQType& pq, unordered_set<int64_t>& seen, int64_t x, int64_t r) {
        if (x * r <= x) return;
        if (seen.find(x * r) != seen.end()) return;
        pq.push(x * r);
        seen.insert(x * r);
    }
};
