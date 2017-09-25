// https://leetcode.com/problems/happy-number/

class Solution {
    
public:
    bool isHappy(int n) {
        unordered_set<int> seen;
        bool ans = true;
        
        for (int x = n; x != 1; x = step(x)) {
            auto it = seen.find(x);
            if (it == seen.end()) {
                seen.insert(x);
            } else {
                ans = false;
                break;
            }
        }
        
        return ans;
    }
    
    int step(int n) {
        int m = 0;
        
        while (n != 0) {
            int d = n % 10;
            m += d * d;
            n /= 10;
        }
        
        return m;
    }
};
