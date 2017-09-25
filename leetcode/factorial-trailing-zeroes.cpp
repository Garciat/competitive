// https://leetcode.com/problems/factorial-trailing-zeroes/

/*

basic algo:
    
    for each i up to n:
        count the number of 2-factors of i
        count the number of 5-factors of i
    
    answer = min(count of 2's, count of 5's)
    
    to count number of k-factors of x:
        while x is divisible by k:
            count += 1
            x /= k


proper algo:
    
    print the answer for a range of n, look at the pattern
    
    notice that the answer will be
          n div 5
        + n div 25
        + n div 125
        + ...
        
        i.e.:
        
        sum[i, n div (5 ^ i)] while (5 ^ i) <= (???) n

fail:
    overflow with int

*/

class Solution {
public:
    int trailingZeroes(int n) {
        long long ans = 0;
        
        long long powOf5 = 5;
        
        while (powOf5 <= n) {
            long long k = n / powOf5;
            
            ans += k;
            
            powOf5 *= 5;
        }
        
        return ans;
    }
};
