// https://leetcode.com/problems/climbing-stairs/

class Solution {
    
    unordered_map<int, int> mem;
    
public:
    int climbStairs(int n) {
        return work(n);
    }
    
    int work(int n) {
        if (n < 0)
            return 0;
        if (n == 0)
            return 1;
        auto it = mem.find(n);
        if (it != mem.end())
            return it->second;
        return mem[n] = work(n-2) + work(n-1);
    }
};
