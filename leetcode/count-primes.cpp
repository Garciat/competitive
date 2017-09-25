// https://leetcode.com/problems/count-primes/

class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;
        
        vector<bool> sieve(n, true);
        sieve[0] = 0;
        sieve[1] = 0;
        sieve[2] = 1;
        
        for (int i = 4; i < n; i += 2)
            sieve[i] = 0;
        
        for (int i = 3; i < n; i += 2) {
            for (int j = 2; j < n/i + 1; ++j) {
                sieve[i*j] = 0;
            }
        }
        
        int ans = 0;
        for (bool b : sieve)
            ans += b;
        return ans;
    }
};
